import streamlit as st
import requests
import pandas as pd
import numpy as np
import time

# Function to fetch sensor data from the Arduino server
def get_sensor_data():
    response = requests.get('http://192.168.1.17')
    if response.status_code == 200:
        return response.json()
    else:
        return None

# Streamlit app
st.title('Gestion Chambre de Pousse')
st.subheader('Pour des brioches et Pizza au top !')

# Placeholder to display sensor data
placeholder = st.empty()

try:
    while True:
        # Initial data fetch
        sensor_data = get_sensor_data()

        with placeholder.container():
            if sensor_data:
                st.success('Connected to sensors')
                st.write(f"**Hardware:** {sensor_data['hardware']}")
                st.write(f"**Temperature:** {sensor_data['variables']['temperature']}°C")
                st.write(f"**Humidity:** {sensor_data['variables']['humidity']}%")

                # Simulate historical data for demonstration purposes
                # TODO Change this
                historical_data = pd.DataFrame({
                    'timestamp': pd.date_range(start='now', periods=10, freq='h'),
                    'temperature': np.random.normal(sensor_data['variables']['temperature'], 1, 10),
                    'humidity': np.random.normal(sensor_data['variables']['humidity'], 1, 10)
                })

                st.line_chart(historical_data[['temperature', 'humidity']])
            else:
                st.error('Failed to retrieve sensor data')
    
        # Wait for 10 seconds before refreshing
        time.sleep(10)

        # Fetch updated sensor data
        sensor_data = get_sensor_data()

except KeyboardInterrupt:
    print("Streamlit app stopped by user.")
