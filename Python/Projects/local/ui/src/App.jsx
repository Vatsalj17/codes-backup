import React, { useState, useEffect, useRef } from 'react';
import { Link } from 'react-router-dom';

function App() {
  // All state declarations moved to the top, as required by React
  const [files, setFiles] = useState([]);
  const [folders, setFolders] = useState([]);
  const [selectedFiles, setSelectedFiles] = useState(null);
  const [message, setMessage] = useState({ text: '', type: '' });
  const [isAuthenticated, setIsAuthenticated] = useState(!!localStorage.getItem('accessToken'));
  
  const fileInputRef = useRef(null);
  const folderInputRef = useRef(null);

  const getAuthHeaders = () => {
    const token = localStorage.getItem('accessToken');
    return {
      'Authorization': `Bearer ${token}`,
    };
  };

  const fetchItems = async () => {
    try {
      const response = await fetch('/api/files/', { headers: getAuthHeaders() });
      if (response.status === 401) {
        setIsAuthenticated(false);
        localStorage.removeItem('accessToken');
        return;
      }
      if (!response.ok) throw new Error('Network response was not ok');
      const data = await response.json();
      setFiles(data.files || []);
      setFolders(data.folders || []);
    } catch (error) {
      console.error("Failed to fetch items:", error);
      setFiles([]);
      setFolders([]);
      showMessage('Failed to fetch items. Is the server running?', 'error');
    }
  };

  useEffect(() => {
    if (isAuthenticated) {
      fetchItems();
    }
  }, [isAuthenticated]);

  const showMessage = (text, type, duration = 3000) => {
    setMessage({ text, type });
    setTimeout(() => setMessage({ text: '', type: '' }), duration);
  };

  const handleFileChange = (event) => {
    setSelectedFiles(event.target.files);
  };

  const handleUpload = async () => {
    if (!selectedFiles) {
      showMessage('Please select a file or folder first!', 'error');
      return;
    }

    const formData = new FormData();
    for (const file of selectedFiles) {
        formData.append('files', file);
        formData.append('paths', file.webkitRelativePath ? file.webkitRelativePath.substring(0, file.webkitRelativePath.lastIndexOf('/')) : "");
    }

    try {
      const response = await fetch('/api/upload/', {
        method: 'POST',
        headers: { ...getAuthHeaders() },
        body: formData,
      });

      if (response.status === 401) setIsAuthenticated(false);
      else if (response.status === 409) {
        const errorData = await response.json();
        showMessage(errorData.detail, 'error');
      } else if (!response.ok) {
        throw new Error('Upload failed');
      } else {
        const data = await response.json();
        showMessage(data.message, 'success');
        fetchItems();
        setSelectedFiles(null);
        if(fileInputRef.current) fileInputRef.current.value = "";
        if(folderInputRef.current) folderInputRef.current.value = "";
      }
    } catch (error) {
      console.error("Upload error:", error);
      showMessage('Error uploading file(s).', 'error');
    }
  };

  const handleDelete = async (itemName) => {
    if (!confirm(`Are you sure you want to delete ${itemName}?`)) return;

    try {
      const response = await fetch(`/api/delete/${itemName}`, {
        method: 'DELETE',
        headers: getAuthHeaders(),
      });
      if (response.status === 401) setIsAuthenticated(false);
      else if (!response.ok) throw new Error('Delete failed');
      else {
        const data = await response.json();
        showMessage(data.message, 'success');
        fetchItems();
      }
    } catch (error) {
      console.error("Delete error:", error);
      showMessage('Error deleting item.', 'error');
    }
  };
  
  const Login = ({ onLoginSuccess }) => {
    const [password, setPassword] = useState('');
    const [error, setError] = useState('');
    const [isPasswordVisible, setIsPasswordVisible] = useState(false); // <-- 1. Add state for visibility

    const handleLogin = async (e) => {
      e.preventDefault();
      setError('');

      const formData = new FormData();
      formData.append('username', 'user');
      formData.append('password', password);

      try {
        const response = await fetch('/api/token', {
          method: 'POST',
          body: formData,
        });

        if (!response.ok) {
          throw new Error('Login failed. Please check the password.');
        }

        const data = await response.json();
        localStorage.setItem('accessToken', data.access_token);
        onLoginSuccess();
      } catch (err) {
        setError(err.message);
      }
    };

    // <-- 2. A simple toggle function
    const togglePasswordVisibility = () => {
      setIsPasswordVisible(!isPasswordVisible);
    };

    return (
      <div className="flex items-center justify-center min-h-screen bg-base">
        <div className="w-full max-w-md p-8 space-y-6 bg-crust rounded-lg shadow-lg">
          <h1 className="text-3xl font-bold text-center text-mauve">Login to Local Share</h1>
          <form onSubmit={handleLogin} className="space-y-6">
            <div>
              <label htmlFor="password" className="text-sm font-bold text-subtext1 block mb-2">Password</label>
              {/* <-- 3. Wrap input and button in a relative container */}
              <div className="relative">
                <input
                  id="password"
                  // <-- 4. Set type based on state
                  type={isPasswordVisible ? 'text' : 'password'}
                  value={password}
                  // Note: I also fixed a small typo here, was 'e.taget.value'
                  onChange={(e) => setPassword(e.target.value)} 
                  // <-- 5. Add padding-right to make space for the button
                  className="w-full p-3 pr-10 bg-mantle rounded-md focus:outline-none focus:ring-2 focus:ring-mauve"
                  required
                />
                {/* <-- 6. The Toggle Button --> */}
                <button
                  type="button" // Important: prevents form submission
                  onClick={togglePasswordVisibility}
                  className="absolute inset-y-0 right-0 flex items-center justify-center h-full w-10 text-overlay1 hover:text-text"
                  aria-label={isPasswordVisible ? "Hide password" : "Show password"}
                >
                  {isPasswordVisible ? (
                    // Eye-Off Icon (Password is visible, show "hide" icon)
                    <svg xmlns="http://www.w3.org/2000/svg" className="h-5 w-5" fill="none" viewBox="0 0 24 24" stroke="currentColor" strokeWidth={2}>
                      <path strokeLinecap="round" strokeLinejoin="round" d="M13.875 18.825A10.05 10.05 0 0112 19c-4.477 0-8.268-2.943-9.542-7 1.274-4.057 5.064-7 9.542-7 1.866 0 3.64.59 5.038 1.575M10 12a2 2 0 11-4 0 2 2 0 014 0z" />
                      <path strokeLinecap="round" strokeLinejoin="round" d="M3 3l18 18" />
                    </svg>
                  ) : (
                    // Eye Icon (Password is hidden, show "show" icon)
                    <svg xmlns="http://www.w3.org/2000/svg" className="h-5 w-5" fill="none" viewBox="0 0 24 24" stroke="currentColor" strokeWidth={2}>
                      <path strokeLinecap="round" strokeLinejoin="round" d="M15 12a3 3 0 11-6 0 3 3 0 016 0z" />
                      <path strokeLinecap="round" strokeLinejoin="round" d="M2.458 12C3.732 7.943 7.523 5 12 5c4.478 0 8.268 2.943 9.542 7-1.274 4.057-5.064 7-9.542 7-4.477 0-8.268-2.943-9.542-7z" />
                    </svg>
                  )}
                </button>
              </div>
            </div>
            {error && <p className="text-red text-center">{error}</p>}
            <button type="submit" className="w-full py-3 px-4 bg-pink hover:bg-mauve text-base font-bold rounded-md transition-colors">
              Login
            </button>
          </form>
        </div>
      </div>
    );
  };
  if (!isAuthenticated) {
    return <Login onLoginSuccess={() => setIsAuthenticated(true)} />;
  }

  return (
    <div className="bg-base text-text min-h-screen font-sans">
      <div className="container mx-auto p-4 md:p-8">
        <header className="flex flex-col sm:flex-row justify-between items-center mb-8">
          <h1 className="text-4xl md:text-5xl font-bold text-mauve">Bendocs Local Share</h1>
          <Link to="/editor">
            <button className="mt-4 sm:mt-0 bg-pink hover:bg-mauve text-base font-bold py-2 px-6 rounded-full transition-all duration-300 shadow-lg shadow-pink/30 hover:shadow-mauve/50">
              Live Editor
            </button>
          </Link>
        </header>

        {message.text && (
          <div className={`p-4 mb-6 rounded-md text-center ${message.type === 'success' ? 'bg-green/20 text-green' : 'bg-red/20 text-red'}`}>
            {message.text}
          </div>
        )}

        <div className="bg-crust rounded-lg shadow-lg p-6 mb-8">
          <h2 className="text-2xl font-semibold mb-4 border-b border-surface0 pb-2 text-rosewater">Upload Files or a Folder</h2>
          {/* This main container now stacks vertically by default */}
          <div className="flex flex-col sm:flex-row items-center gap-4">
            
            {/* START: Redesigned Responsive Upload Section */}
            {/* This inner container also stacks vertically and becomes a row on larger screens */}
            <div className="flex-grow bg-mantle p-2 rounded-lg sm:rounded-full flex flex-col sm:flex-row items-center justify-between w-full gap-2 sm:gap-0">
              
              {/* This group contains the two select buttons */}
              <div className="flex items-center gap-2 w-full sm:w-auto justify-center p-1">
                <input
                  type="file"
                  multiple
                  onChange={handleFileChange}
                  ref={fileInputRef}
                  id="file-upload"
                  className="hidden"
                />
                <label
                  htmlFor="file-upload"
                  className="cursor-pointer bg-mauve hover:bg-pink text-base font-semibold py-2 px-5 rounded-full transition-colors whitespace-nowrap"
                >
                  Select Files
                </label>
                <input
                  type="file"
                  onChange={handleFileChange}
                  ref={folderInputRef}
                  webkitdirectory=""
                  directory=""
                  id="folder-upload"
                  className="hidden"
                />
                <label
                  htmlFor="folder-upload"
                  className="cursor-pointer bg-lavender hover:bg-rosewater text-base font-semibold py-2 px-5 rounded-full transition-colors whitespace-nowrap"
                >
                  Select Folder
                </label>
              </div>

              {/* Status text appears below buttons on mobile, and on the left on larger screens */}
              <span className="text-subtext0 sm:pl-4 text-sm truncate sm:pr-2 order-first sm:order-last text-center sm:text-left w-full sm:w-auto">
                {selectedFiles ? `${selectedFiles.length} item(s) selected` : "No items selected"}
              </span>

            </div>
            {/* END: Redesigned Responsive Upload Section */}
            
            <button
              onClick={handleUpload}
              disabled={!selectedFiles}
              className="w-full sm:w-auto bg-teal hover:bg-green disabled:bg-surface1 disabled:cursor-not-allowed text-base font-bold py-2 px-6 rounded-full transition-all duration-300 shadow-lg shadow-teal/30 hover:shadow-green/50"
            >
              Upload
            </button>
          </div>
        </div>

        <div className="bg-crust rounded-lg shadow-lg p-6">
          <h2 className="text-2xl font-semibold mb-4 border-b border-surface0 pb-2 text-rosewater">Available Items</h2>
          <div className="space-y-3">
            {folders.length > 0 && folders.map((folder) => (
                <div key={folder} className="flex items-center justify-between bg-surface0/50 p-3 rounded-md hover:bg-surface1 transition-colors duration-200">
                  <span className="truncate pr-4 text-yellow">{folder}/</span>
                  <div className="flex items-center gap-3 flex-shrink-0">
                    <a
                      href={`/api/download/${folder}?token=${localStorage.getItem('accessToken')}`}
                      target="_blank"
                      rel="noopener noreferrer"
                      className="text-green hover:text-teal font-medium"
                    >
                      Download
                    </a>
                    <button
                      onClick={() => handleDelete(folder)}
                      className="text-red hover:text-maroon font-medium"
                    >
                      Delete
                    </button>
                  </div>
                </div>
            ))}
            {files.length > 0 && files.map((filename) => (
                <div key={filename} className="flex items-center justify-between bg-surface0/50 p-3 rounded-md hover:bg-surface1 transition-colors duration-200">
                  <span className="truncate pr-4">{filename}</span>
                  <div className="flex items-center gap-3 flex-shrink-0">
                     <a
                      href={`/api/download/${filename}?token=${localStorage.getItem('accessToken')}`}
                      target="_blank"
                      rel="noopener noreferrer"
                      className="text-green hover:text-teal font-medium"
                    >
                      Download
                    </a>
                    <button
                      onClick={() => handleDelete(filename)}
                      className="text-red hover:text-maroon font-medium"
                    >
                      Delete
                    </button>
                  </div>
                </div>
            ))}
            {files.length === 0 && folders.length === 0 && (
              <p className="text-subtext1 text-center py-4">No files or folders have been uploaded yet.</p>
            )}
          </div>
        </div>
      </div>
    </div>
  );
}

export default App;
