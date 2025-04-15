import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
import joblib

def preprocess_data(filename):
    # Load data
    df = pd.read_csv(filename, parse_dates=['timestamp'])
    
    # Sort by timestamp
    df = df.sort_values('timestamp')
    
    # Feature engineering
    df['time_diff'] = df['timestamp'].diff().dt.total_seconds().fillna(0)
    df['moisture_diff'] = df['soil_moisture'].diff().fillna(0)
    df['moisture_rate'] = df['moisture_diff'] / df['time_diff'].replace(0, 1)
    
    # Calculate time from >70% to 40% moisture for each cycle
    cycles = []
    in_cycle = False
    start_time = None
    start_moisture = None
    
    for idx, row in df.iterrows():
        if not in_cycle and row['soil_moisture'] < 70:
            in_cycle = True
            start_time = row['timestamp']
            start_moisture = row['soil_moisture']  # Fixed typo: was 'soil_misture'
        elif in_cycle and row['soil_moisture'] >= 40:
            in_cycle = False
            end_time = row['timestamp']
            duration = (end_time - start_time).total_seconds()
            cycles.append({
                'start_time': start_time,
                'duration': duration,
                'start_temp': df.loc[df['timestamp'] == start_time, 'temperature'].values[0],
                'start_humidity': df.loc[df['timestamp'] == start_time, 'humidity'].values[0],
                'avg_light': df[(df['timestamp'] >= start_time) & (df['timestamp'] <= end_time)]['light_intensity'].mean()
            })
    
    # Create moisture cycle dataset
    moisture_df = pd.DataFrame(cycles)
    
    # Create water level dataset
    water_df = df[df['water_level'] <= 30].copy()
    water_df = water_df.groupby((water_df['water_level'].diff() < 0).cumsum()).agg({
        'timestamp': ['first', 'last'],
        'water_level': ['first', 'last'],
        'temperature': 'mean',
        'humidity': 'mean',
        'light_intensity': 'mean'
    })
    water_df.columns = ['start_time', 'end_time', 'start_level', 'end_level', 'avg_temp', 'avg_humidity', 'avg_light']
    water_df['duration'] = (water_df['end_time'] - water_df['start_time']).dt.total_seconds()
    
    # Save processed data
    moisture_df.to_csv('processed_moisture_data.csv', index=False)
    water_df.to_csv('processed_water_data.csv', index=False)
    
    return moisture_df, water_df

if __name__ == "__main__":
    moisture_data, water_data = preprocess_data('modified_sensor_data.csv')