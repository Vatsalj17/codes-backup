import React, { useState, useEffect, useRef } from 'react';
import { Link } from 'react-router-dom';

function LiveEditor() {
  const [content, setContent] = useState('');
  const [message, setMessage] = useState({ text: '', type: '' });
  const socket = useRef(null);
  const textAreaRef = useRef(null); // Ref for the textarea element

  useEffect(() => {
    const wsProtocol = window.location.protocol === 'https:' ? 'wss:' : 'ws:';
    const wsUrl = `${wsProtocol}//${window.location.host}/api/ws/editor`;

    socket.current = new WebSocket(wsUrl);

    socket.current.onopen = () => console.log('WebSocket connected');
    socket.current.onmessage = (event) => setContent(event.data);
    socket.current.onclose = () => {
      console.log('WebSocket disconnected');
      showMessage('Connection to server lost.', 'error');
    };
    socket.current.onerror = (error) => {
      console.error('WebSocket error:', error);
      showMessage('Could not connect to the live editor.', 'error');
    };

    return () => {
      if (socket.current) {
        socket.current.close();
      }
    };
  }, []);

  const showMessage = (text, type, duration = 3000) => {
    setMessage({ text, type });
    setTimeout(() => setMessage({ text: '', type: '' }), duration);
  };

  const handleContentChange = (event) => {
    setContent(event.target.value);
  };

  const pushContent = () => {
    if (socket.current && socket.current.readyState === WebSocket.OPEN) {
      socket.current.send(content);
      showMessage('Content updated!', 'success');
    } else {
      showMessage('Not connected to the server.', 'error');
    }
  };

  const copyToClipboard = () => {
    // Modern way: using navigator.clipboard (secure contexts)
    if (navigator.clipboard && window.isSecureContext) {
      navigator.clipboard.writeText(content)
        .then(() => showMessage('Copied to clipboard!', 'success'))
        .catch(() => showMessage('Failed to copy!', 'error'));
    } else {
      // Fallback for older browsers or insecure contexts
      if (textAreaRef.current) {
        textAreaRef.current.select();
        try {
          document.execCommand('copy');
          showMessage('Copied to clipboard!', 'success');
        } catch (err) {
          showMessage('Failed to copy!', 'error');
        }
      }
    }
  };

  return (
    <div className="bg-base text-text min-h-screen font-sans">
      <div className="container mx-auto p-4 md:p-8">
        <header className="text-center mb-8">
          <h1 className="text-4xl md:text-5xl font-bold text-teal">Live Text Editor</h1>
        </header>

        {message.text && (
          <div className={`p-4 mb-6 rounded-md text-center ${message.type === 'success' ? 'bg-green/20 text-green' : 'bg-red/20 text-red'}`}>
            {message.text}
          </div>
        )}

        <div className="bg-crust rounded-lg shadow-lg p-6 mb-8">
          {/* We wrap the textarea and button in a relative container */}
          <div className="relative">
            <textarea
              ref={textAreaRef}
              className="w-full h-96 p-4 bg-mantle text-text rounded-md resize-none focus:outline-none focus:ring-2 focus:ring-teal shadow-inner shadow-base"
              value={content}
              onChange={handleContentChange}
              placeholder="Start typing..."
            />
            <button
              onClick={copyToClipboard}
              className="absolute top-3 right-3 p-2 bg-surface0 hover:bg-surface1 rounded-md transition-colors duration-200"
              aria-label="Copy to clipboard"
            >
              <svg xmlns="http://www.w3.org/2000/svg" className="h-5 w-5 text-lavender" fill="none" viewBox="0 0 24 24" stroke="currentColor">
                <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M8 16H6a2 2 0 01-2-2V6a2 2 0 012-2h8a2 2 0 012 2v2m-6 12h8a2 2 0 002-2v-8a2 2 0 00-2-2h-8a2 2 0 00-2 2v8a2 2 0 002 2z" />
              </svg>
            </button>
          </div>
          <div className="flex items-center justify-end gap-4 mt-4">
            <button
              onClick={pushContent}
              className="w-full sm:w-auto bg-teal hover:bg-green text-base font-bold py-2 px-6 rounded-full transition-all duration-300 shadow-lg shadow-teal/30 hover:shadow-green/50"
            >
              Push Changes
            </button>
          </div>
        </div>

        <div className="text-center mt-8">
          <Link to="/" className="text-pink hover:text-mauve transition-colors duration-300">
            &larr; Back to File Share
          </Link>
        </div>
      </div>
    </div>
  );
}

export default LiveEditor;
