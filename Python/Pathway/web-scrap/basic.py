import requests
from bs4 import BeautifulSoup
import sys
from typing import List, Dict
import re

def get_repositories(username: str) -> List[Dict]:
    """Fetch all repositories for a given GitHub username."""
    repos = []
    page = 1
    
    while True:
        url = f"https://github.com/{username}?page={page}&tab=repositories"
        response = requests.get(url)
        
        if response.status_code != 200:
            print(f"Error: Unable to fetch repositories for user '{username}'")
            print(f"Status code: {response.status_code}")
            return []
        
        soup = BeautifulSoup(response.content, 'html.parser')
        repo_list = soup.find('div', {'id': 'user-repositories-list'})
        
        if not repo_list:
            break
        
        repo_items = repo_list.find_all('li')
        
        if not repo_items:
            break
        
        for item in repo_items:
            repo_link = item.find('a', {'itemprop': 'name codeRepository'})
            if repo_link:
                repo_name = repo_link.text.strip()
                repo_url = f"https://github.com{repo_link['href']}"
                
                desc_elem = item.find('p', {'itemprop': 'description'})
                description = desc_elem.text.strip() if desc_elem else "No description"
                
                repos.append({
                    'name': repo_name,
                    'url': repo_url,
                    'description': description
                })
        
        page += 1
        
        # Check if there's a next page
        next_button = soup.find('a', {'class': 'next_page'})
        if not next_button or 'disabled' in next_button.get('class', []):
            break
    
    return repos

def get_readme(username: str, repo_name: str) -> str:
    """Fetch the README content for a repository."""
    readme_url = f"https://raw.githubusercontent.com/{username}/{repo_name}/main/README.md"
    response = requests.get(readme_url)
    
    if response.status_code == 200:
        return response.text
    
    # Try master branch if main doesn't exist
    readme_url = f"https://raw.githubusercontent.com/{username}/{repo_name}/master/README.md"
    response = requests.get(readme_url)
    
    if response.status_code == 200:
        return response.text
    
    return "README not found"

def print_separator(char='=', length=80):
    """Print a separator line."""
    print(char * length)

def pretty_print_repositories(username: str):
    """Fetch and pretty print all repositories with details."""
    print(f"\n{'=' * 80}")
    print(f"GitHub Repositories for: {username}".center(80))
    print(f"{'=' * 80}\n")
    
    repos = get_repositories(username)
    
    if not repos:
        print("No repositories found or user doesn't exist.")
        return
    
    print(f"Found {len(repos)} repositories\n")
    
    for idx, repo in enumerate(repos, 1):
        print_separator('=')
        print(f"\n[{idx}] {repo['name']}")
        print_separator('-')
        print(f"URL: {repo['url']}")
        print(f"Description: {repo['description']}")
        print_separator('-')
        print("\nREADME:")
        print_separator('-')
        
        readme = get_readme(username, repo['name'])
        
        # Truncate very long READMEs for display
        if len(readme) > 2000:
            print(readme[:2000])
            print("\n... (README truncated, visit repository for full content)")
        else:
            print(readme)
        
        print("\n")

def main():
    """Main function to run the script."""
    if len(sys.argv) < 2:
        print("Usage: python basic.py <github_username>")
        print("Example: python basic.py torvalds")
        sys.exit(1)
    
    username = sys.argv[1]
    
    try:
        pretty_print_repositories(username)
    except Exception as e:
        print(f"An error occurred: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()
