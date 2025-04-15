import numpy as np
import joblib
import tensorflow as tf
from tensorflow import keras
from tensorflow.keras import layers

def sklearn_to_tflite_header(model, input_shape, output_header_name, var_name):
    """
    Convert scikit-learn model to ESP32-compatible .h file without Python ops
    Args:
        model: Trained scikit-learn model
        input_shape: Tuple of input shape (e.g., (3,) for moisture model)
        output_header_name: Output .h filename
        var_name: C variable name prefix
    """
    # Create a representative dataset from the model's training data
    # (You'll need to modify this based on your actual training data)
    samples = np.random.rand(100, *input_shape).astype(np.float32)
    
    # Create a pure TensorFlow model that approximates the sklearn model
    keras_model = keras.Sequential([
        layers.Dense(10, activation='relu', input_shape=input_shape),
        layers.Dense(1)  # Single output for regression
    ])
    
    # Train the Keras model to mimic the sklearn model
    keras_model.compile(optimizer='adam', loss='mse')
    keras_model.fit(
        samples,
        model.predict(samples),
        epochs=50,
        verbose=0
    )
    
    # Convert to TFLite with optimizations
    converter = tf.lite.TFLiteConverter.from_keras_model(keras_model)
    converter.optimizations = [tf.lite.Optimize.DEFAULT]
    converter.target_spec.supported_ops = [tf.lite.OpsSet.TFLITE_BUILTINS]
    
    try:
        tflite_model = converter.convert()
    except Exception as e:
        print(f"Conversion failed: {str(e)}")
        return

    # Generate C header
    with open(output_header_name, 'w') as f:
        # Header guard
        f.write(f"#ifndef {var_name.upper()}_H\n")
        f.write(f"#define {var_name.upper()}_H\n\n")
        
        # Model data
        f.write(f"alignas(8) const unsigned char {var_name}_tflite[] = {{\n  ")
        f.write(",\n  ".join(
            ", ".join(f"0x{b:02x}" for b in tflite_model[i:i+12])
            for i in range(0, len(tflite_model), 12)
        ))
        f.write("\n};\n\n")
        
        # Length
        f.write(f"const unsigned int {var_name}_tflite_len = {len(tflite_model)};\n\n")
        f.write("#endif\n")
    
    print(f"Successfully generated {output_header_name} ({len(tflite_model)} bytes)")

if __name__ == "__main__":
    try:
        # Load your trained models
        moisture_model = joblib.load('moisture_model.joblib')
        water_level_model = joblib.load('water_level_model.joblib')

        # Convert directly to .h files
        sklearn_to_tflite_header(
            moisture_model,
            input_shape=(3,),
            output_header_name="moisture_model.h",
            var_name="moisture_model"
        )

        sklearn_to_tflite_header(
            water_level_model,
            input_shape=(4,),
            output_header_name="water_level_model.h",
            var_name="water_level_model"
        )
    except Exception as e:
        print(f"Error during conversion: {str(e)}")