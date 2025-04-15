import pandas as pd
from sklearn.ensemble import RandomForestRegressor
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_absolute_error
import joblib

def train_water_level_model():
    # Load processed data
    df = pd.read_csv('processed_water_data.csv')
    
    # Features and target
    X = df[['start_level', 'avg_temp', 'avg_humidity', 'avg_light']]
    y = df['duration']
    
    # Train-test split
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
    
    # Train model
    model = RandomForestRegressor(n_estimators=10, max_depth=5, random_state=42)  # Keep it small for ESP32
    model.fit(X_train, y_train)
    
    # Evaluate
    preds = model.predict(X_test)
    mae = mean_absolute_error(y_test, preds)
    print(f"Water Level Model MAE: {mae} seconds")
    
    # Save model
    joblib.dump(model, 'water_level_model.joblib')
    print("Water level model saved as 'water_level_model.joblib'")
    
    return model

def predict_time_to_empty(current_level, temp, humidity, light_intensity, model_path='water_level_model.joblib'):
    # Load model
    model = joblib.load(model_path)
    
    # Create input array
    input_data = [[current_level, temp, humidity, light_intensity]]
    
    # Predict
    seconds = model.predict(input_data)[0]
    
    return max(seconds, 60)  # Ensure at least 1 minute

if __name__ == "__main__":
    model = train_water_level_model()
    # Test prediction
    print("Sample prediction:", predict_time_to_empty(20, 28, 65, 200000, 'water_level_model.joblib'))