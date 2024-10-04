import random
import string


def generate_random_string(length=22):
    """Generates a random string of specified length.

    Args:
        length: The desired length of the string (default is 22).

    Returns:
        A random string of the specified length, or None if an error occurs.  
    """
    try:
        # Define the character set
        characters = string.ascii_lowercase + \
            string.ascii_uppercase + "$_" + string.digits

        # Check if the length is valid.  A negative length is not allowed.
        if length < 0:
            print("Error: Length must be a non-negative integer.")
            return None

        # Generate the random string
        random_string = ''.join(random.choice(characters)
                                for i in range(length))
        return random_string

    except Exception as e:
        print(f"An error occurred: {e}")
    return None


# Get a 22-character random string
with open(f'random_strings.txt', 'w') as file:
    for i in range(10):
        random_string = generate_random_string()
        file.write(random_string + '\n')
