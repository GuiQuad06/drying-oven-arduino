from flask import Flask, render_template
import requests

app = Flask(__name__)

@app.route("/")
def home():
    try:
        response = requests.get('http://192.168.1.17', timeout=5)
        response.raise_for_status()  # Raise an HTTPError for bad responses (4xx and 5xx)
        json_data = response.json()
    except requests.exceptions.RequestException as e:
        # Log the error and provide fallback data
        print(f"Error fetching data: {e}")
        json_data = {"variables": {"temperature": "N/A", "humidity": "N/A"}}
    except ValueError:
        # Handle JSON decoding errors
        print("Error decoding JSON response")
        json_data = {"variables": {"temperature": "N/A", "humidity": "N/A"}}

    return render_template("index.html", data=json_data)

if __name__ == "__main__":
    app.run(debug=True)
