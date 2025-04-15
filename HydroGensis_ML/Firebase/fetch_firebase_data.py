import firebase_admin
from firebase_admin import credentials, db
import pandas as pd

# Initialize Firebase Admin SDK
cred = credentials.Certificate("firebase_admin_sdk.json")
firebase_admin.initialize_app(cred, {
    'databaseURL': 'https://**************.firebaseio.com/'
})

# Reference to your data
ref = db.reference("/")  # or /your/path if data is nested

# Fetch the data
data = ref.get()

# Debugging step
print("Fetched data:", data)

# Check if data is valid
if data is None:
    print("No data found in Firebase.")
else:
    # Handle both flat dict or nested timestamped dict
    if all(isinstance(v, dict) for v in data.values()):
        df = pd.DataFrame(data).T  # multiple timestamped entries
    else:
        df = pd.DataFrame([data])  # single entry

    print("DataFrame:")
    print(df)

    # Save to CSV for ML processing later
    df.to_csv("firebase_data.csv", index=False)
