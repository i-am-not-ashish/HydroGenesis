import requests

# Replace with your ESP32's IP address
esp32_ip = "192.168.137.15"
url = f"http://{esp32_ip}/data"

# Fetch the CSV file
response = requests.get(url)

# Save the file to your laptop
if response.status_code == 200:
    with open("sensor_data.csv", "wb") as file:
        file.write(response.content)
    print("CSV file downloaded successfully.")
else:
    print(f"Failed to download file. Status code: {response.status_code}")