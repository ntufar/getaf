
import mysql.connector
import os

# --- Configuration ---
# Replace with your MySQL server details.
# It's recommended to use environment variables for security.
DB_HOST = os.environ.get('DB_HOST', 'localhost')
DB_USER = os.environ.get('DB_USER', 'root')
DB_PASSWORD = os.environ.get('DB_PASSWORD', 'password')
DB_SCHEMA_FILE = os.path.join('..', 'Database', 'schema.sql')

def setup_database():
    """Connects to MySQL, creates the database, and executes the schema script."""
    try:
        # Connect to MySQL server
        db = mysql.connector.connect(
            host=DB_HOST,
            user=DB_USER,
            password=DB_PASSWORD
        )
        cursor = db.cursor()

        print(f"Successfully connected to MySQL server at {DB_HOST}.")

        # Read the schema file
        with open(DB_SCHEMA_FILE, 'r') as f:
            schema_sql = f.read()

        # Execute the schema script (can contain multiple statements)
        for result in cursor.execute(schema_sql, multi=True):
            if result.with_rows:
                print(f"Executed: {result.statement}")
            else:
                print(f"Executed: {result.statement}, Rows affected: {result.rowcount}")


        print("Database schema created successfully.")

        db.commit()

    except mysql.connector.Error as err:
        print(f"Error: {err}")
    finally:
        if 'db' in locals() and db.is_connected():
            cursor.close()
            db.close()
            print("MySQL connection closed.")

if __name__ == "__main__":
    print("Setting up the database...")
    setup_database()
