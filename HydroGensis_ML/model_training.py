from data_preprocessing import preprocess_data
from moisture_model import train_moisture_model
from water_level_model import train_water_level_model

def main():
    print("Preprocessing data...")
    moisture_data, water_data = preprocess_data('sensor_data.csv')
    
    print("\nTraining moisture model...")
    moisture_model = train_moisture_model()
    
    print("\nTraining water level model...")
    water_level_model = train_water_level_model()
    
    print("\nTraining complete!")

if __name__ == "__main__":
    main()