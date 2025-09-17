import mysql.connector
import os

# Database connection details (placeholders - replace with actual credentials or environment variables)
DB_CONFIG = {
    'host': 'localhost',
    'user': 'ntufar',
    'password': 'abc123', # Replace with your MySQL root password
    'database': 'getaf_db'
}

SCHEMA_FILE = os.path.join(os.path.dirname(__file__), '..', 'Database', 'schema.sql')

def setup_database():
    """
    Connects to MySQL, creates the database if it doesn't exist,
    and then creates tables based on the schema.sql file.
    """
    try:
        # Connect to MySQL server (without specifying a database initially)
        cnx = mysql.connector.connect(
            host=DB_CONFIG['host'],
            user=DB_CONFIG['user'],
            password=DB_CONFIG['password']
        )
        cursor = cnx.cursor()

        # Create the database if it doesn't exist
        try:
            cursor.execute(f"CREATE DATABASE IF NOT EXISTS {DB_CONFIG['database']}")
            print(f"Database '{DB_CONFIG['database']}' ensured to exist.")
        except mysql.connector.Error as err:
            print(f"Failed creating database: {err}")
            return

        # Close connection and reconnect to the specific database
        cursor.close()
        cnx.close()

        cnx = mysql.connector.connect(**DB_CONFIG)
        cursor = cnx.cursor()

        # Read and execute schema.sql
        with open(SCHEMA_FILE, 'r') as f:
            sql_commands = f.read()

        # Split commands by semicolon and execute each
        for command in sql_commands.split(';'):
            command = command.strip()
            if command:
                try:
                    cursor.execute(command)
                    print(f"Executed: {command.splitlines()[0]}...")
                except mysql.connector.Error as err:
                    print(f"Failed to execute command: {command.splitlines()[0]}...\nError: {err}")
                    # Continue to next command or break, depending on desired error handling
                    # For now, we'll print the error and continue
                    pass

        # Commit changes and close connection
        cnx.commit()
        print("Database setup complete.")

    except mysql.connector.Error as err:
        if err.errno == mysql.connector.errorcode.ER_ACCESS_DENIED_ERROR:
            print("Something is wrong with your user name or password")
        elif err.errno == mysql.connector.errorcode.ER_BAD_DB_ERROR:
            print("Database does not exist")
        else:
            print(f"An unexpected error occurred: {err}")
    finally:
        if 'cnx' in locals() and cnx.is_connected():
            cursor.close()
            cnx.close()
            print("MySQL connection closed.")

if __name__ == "__main__":
    setup_database()