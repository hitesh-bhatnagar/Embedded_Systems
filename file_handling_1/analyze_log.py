import time

LOG_FILE = "sensor_log.txt"

def analyze_log():
    try:
        with open(LOG_FILE, "r") as file:
            lines = file.readlines()
            readings = [int(line.strip().split(": ")[1]) for line in lines]
            if readings:
                print(f"Total readings: {len(readings)}")
                print(f"Average value: {sum(readings)/len(readings):.2f}")
                print(f"Max value: {max(readings)}")
                print(f"Min value: {min(readings)}")
            else:
                print("No readings found.")
    except FileNotFoundError:
        print("Log file not found!")

if __name__ == "__main__":
    print("Monitoring sensor log in real-time. Press Ctrl+C to stop.")
    while True:
        analyze_log()
        time.sleep(5) 
