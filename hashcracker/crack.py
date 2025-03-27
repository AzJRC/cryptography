import hashlib
import re
import os

TRIED_LIST_FILE = os.path.join(os.getcwd(), "hashcracker", "tried_password_lists.txt")
HANDLE_USER_PASSWORD_FORMAT = True  # Toggle handling of "user password" format
HASH_ALGORITHMS = ["sha256"]  # Supported hashing algorithms
PASSWORDLIST_DIRNAME = "passwordslists"

# Function to compute hashes
def compute_hash(word, salt, algorithm):
    if algorithm == "sha256":
        return hashlib.sha256((salt + word).encode()).hexdigest(), hashlib.sha256((word + salt).encode()).hexdigest()
    elif algorithm == "sha1":
        return hashlib.sha1((salt + word).encode()).hexdigest(), hashlib.sha1((word + salt).encode()).hexdigest()
    elif algorithm == "md5":
        return hashlib.md5((salt + word).encode()).hexdigest(), hashlib.md5((word + salt).encode()).hexdigest()
    elif algorithm == "sha512":
        return hashlib.sha512((salt + word).encode()).hexdigest(), hashlib.sha512((word + salt).encode()).hexdigest()
    return None, None

# Function to perform dictionary attack
def dictionary_attack(dictionary_file, salt, target_hash):
    try:
        with open(dictionary_file, "r", encoding="utf-8") as file:
            for line in file:
                line = line.strip()
                
                # Handle "user password" format if enabled
                if HANDLE_USER_PASSWORD_FORMAT and " " in line:
                    parts = line.split(" ", 1)
                    word = parts[1]  # Assume second part is the password
                else:
                    word = line
                
                for algo in HASH_ALGORITHMS:
                    hash1, hash2 = compute_hash(word, salt, algo)
                    
                    if hash1 == target_hash or hash2 == target_hash:
                        return word  # Found the password
            
    except FileNotFoundError:
        print(f"File not found: {dictionary_file}")
    except Exception as e:
        print(f"Error reading {dictionary_file}: {e}")
    
    return None  # Not found

# Function to find dictionary files matching "rockyou_#.txt"
def get_dictionaries():
    dict_path = os.path.join(os.getcwd(), "hashcracker", PASSWORDLIST_DIRNAME)
    if not os.path.exists(dict_path):
        print(f" - Passwords directory not found: Attempted directory was {dict_path}")
        return []
    
    files = os.listdir(dict_path)
    regex = re.compile(r"\S+.txt$")
    
    return [os.path.join(dict_path, f) for f in files if regex.match(f)]

# Function to read already tried password lists
def get_tried_lists():
    if not os.path.exists(TRIED_LIST_FILE):
        return set()
    
    with open(TRIED_LIST_FILE, "r", encoding="utf-8") as file:
        return set(line.strip() for line in file)

# Function to mark a dictionary as tried
def mark_as_tried(dictionary_file):
    with open(TRIED_LIST_FILE, "a", encoding="utf-8") as file:
        file.write(dictionary_file + "\n")

# Run dictionary attack on a single file
def run_attack(dictionary_file, salt, target_hash):
    print(f"Trying dictionary: {dictionary_file}")
    
    password = dictionary_attack(dictionary_file, salt, target_hash)
    if password:
        print(f"+ Password found: {password} (from {dictionary_file})\n")
        exit(0)  # Exit since we found the password
    else:
        print(f"- Password not found in {dictionary_file}")
    
    mark_as_tried(dictionary_file)

# Main function
def main():
    dictionaries = get_dictionaries()
    tried_lists = get_tried_lists()
    
    if not dictionaries:
        print(" - No dictionary files found. Make sure the text files exist in the Passwords directory.")
        return
    
    dictionaries_to_try = [d for d in dictionaries if d not in tried_lists]
    
    if not dictionaries_to_try:
        print(" - All available dictionaries have already been tried.")
        return
    
    print(f"+ Found {len(dictionaries_to_try)} new dictionary files: {dictionaries_to_try}")
    
    for dictionary in dictionaries_to_try:
        run_attack(dictionary, salt, target_hash)

# Given values from password.txt
salt = "CqahaPXSeY"
target_hash = "82c6d536367b25f33978825c5a57e65cedf68d2b64930dd62020a308ac1770c1"

# Run the program

if __name__ == "__main__":
    main()
