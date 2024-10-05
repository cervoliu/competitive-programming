import os
import json

# Directory containing the C++ template files
template_dir = 'template/'

# Path to the output snippets file
snippets_file = '.vscode/cpp.code-snippets'

# Function to convert a single C++ file into a VSCode snippet
def generate_snippet(file_path):
    with open(file_path, 'r') as file:
        # Read the entire file content
        content = file.readlines()
    
    # Get the filename without the extension (used as the snippet name and prefix)
    snippet_name = os.path.splitext(os.path.basename(file_path))[0]
    
    # Create the snippet structure
    snippet = {
        "prefix": snippet_name,  # Snippet trigger
        "scope": "cpp",  # Snippet scope (only for C++ files)
        "body": [line.rstrip() for line in content],  # Snippet content, line by line
    }
    
    return snippet_name, snippet

# Function to generate the snippets JSON structure from all C++ files
def generate_snippets(template_dir):
    snippets = {}
    
    for filename in os.listdir(template_dir):
        if filename.endswith('.cpp'):
            file_path = os.path.join(template_dir, filename)
            snippet_name, snippet = generate_snippet(file_path)
            snippets[snippet_name] = snippet
    
    return snippets

# Main function to generate the snippets file
def main():
    snippets = generate_snippets(template_dir)
    
    with open(snippets_file, 'w') as outfile:
        json.dump(snippets, outfile, indent=4)
    
    print(f"Snippets file generated at: {snippets_file}")

if __name__ == '__main__':
    main()