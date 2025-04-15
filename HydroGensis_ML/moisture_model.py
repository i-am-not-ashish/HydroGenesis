import pandas as pd
from sklearn.ensemble import RandomForestRegressor
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_absolute_error
import joblib
import logging
import numpy as np

logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

def train_moisture_model():
    try:
        # Load processed data
        logger.info("Loading processed moisture data...")
        df = pd.read_csv('processed_moisture_data.csv')
        
        if df.empty:
            logger.warning("No data available for training moisture model")
            return None
            
        # If we have only 1 sample, we can't do train-test split
        if len(df) == 1:
            logger.warning("Only 1 sample available - using entire dataset for training")
            X = df[['start_temp', 'start_humidity', 'avg_light']]
            y = df['duration']
            X_train, X_test, y_train, y_test = X, X, y, y
        else:
            # Features and target
            X = df[['start_temp', 'start_humidity', 'avg_light']]
            y = df['duration']
            # Train-test split (only if we have enough samples)
            X_train, X_test, y_train, y_test = train_test_split(
                X, y, test_size=min(0.2, 1/len(df)), 
                random_state=42
            )
        
        # Train model
        logger.info("Training moisture model...")
        model = RandomForestRegressor(
            n_estimators=5 if len(df) < 5 else 10,  # Fewer trees for small datasets
            max_depth=3 if len(df) < 10 else 5,      # Shallower trees for small datasets
            random_state=42
        )
        model.fit(X_train, y_train)
        
        # Evaluate if we have test samples
        if len(X_test) > 0:
            preds = model.predict(X_test)
            mae = mean_absolute_error(y_test, preds)
            logger.info(f"Moisture Model MAE: {mae} seconds")
        else:
            logger.warning("Insufficient data for proper evaluation")
        
        # Save model
        joblib.dump(model, 'moisture_model.joblib')
        logger.info("Moisture model saved as 'moisture_model.joblib'")
        
        return model
    
    except Exception as e:
        logger.error(f"Error training moisture model: {str(e)}")
        raise

def predict_time_to_water(temp, humidity, light_intensity, model_path='moisture_model.joblib'):
    try:
        # Load model
        model = joblib.load(model_path)
        
        # Create input array
        input_data = [[temp, humidity, light_intensity]]
        
        # Predict
        seconds = model.predict(input_data)[0]
        
        return max(seconds, 60)  # Ensure at least 1 minute
    
    except Exception as e:
        logger.error(f"Error making prediction: {str(e)}")
        # Return a default value if prediction fails
        return 3600  # Default to 1 hour

if __name__ == "__main__":
    model = train_moisture_model()
    if model is not None:
        # Test prediction
        print("Sample prediction:", predict_time_to_water(28, 65, 200000, 'moisture_model.joblib'))