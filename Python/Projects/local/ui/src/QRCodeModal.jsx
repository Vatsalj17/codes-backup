import React, { useState, useEffect } from 'react';

const QRCodeModal = ({ isOpen, onClose }) => {
  const [qrCodeSrc, setQrCodeSrc] = useState('');
  const [url, setUrl] = useState(''); // 1. Add new state for the URL
  const [isLoading, setIsLoading] = useState(false);
  const [error, setError] = useState('');

  useEffect(() => {
    // Fetch only if open and we don't have the data yet
    if (isOpen && !qrCodeSrc) { 
      setIsLoading(true);
      setError('');
      fetch('/api/qr-code')
        .then(res => {
          if (!res.ok) throw new Error('Failed to fetch QR code');
          return res.json();
        })
        .then(data => {
          // 2. Set both the QR code and the URL from the API response
          setQrCodeSrc(data.qr_code_base64);
          setUrl(data.url);
        })
        .catch(err => {
          console.error(err);
          setError('Could not load QR code.');
        })
        .finally(() => {
          setIsLoading(false);
        });
    } else if (!isOpen) {
      // Clear data when modal is closed so it refetches next time
      setQrCodeSrc('');
      setUrl('');
    }
  }, [isOpen, qrCodeSrc]); // Dependency on isOpen is key

  if (!isOpen) return null;

  return (
    // Modal Overlay
    <div 
      className="fixed inset-0 bg-base/80 backdrop-blur-sm flex items-center justify-center z-50"
      onClick={onClose}
    >
      {/* Modal Content */}
      <div 
        className="bg-crust p-6 rounded-lg shadow-2xl relative w-80" // Gave it a fixed width
        onClick={e => e.stopPropagation()} // Prevent closing modal when clicking inside
      >
        <h2 className="text-2xl font-bold text-mauve text-center mb-4">Scan to Connect</h2>
        <div className="w-64 h-64 bg-mantle rounded-md flex items-center justify-center mx-auto">
          {isLoading && <p className="text-text">Loading...</p>}
          {error && <p className="text-red">{error}</p>}
          {qrCodeSrc && (
            // 3. THE FIX: Prepend the Data URI scheme here
            <img 
              src={`data:image/png;base64,${qrCodeSrc}`} 
              alt="Server QR Code" 
              className="w-full h-full object-contain rounded-md" 
            />
          )}
        </div>
        
        {/* 4. Display the URL */}
        {url && (
          <p className="text-text text-center mt-4 text-sm font-mono break-all" title="Server URL">
            {url}
          </p>
        )}

        <button
          onClick={onClose}
          className="absolute top-2 right-2 text-overlay2 hover:text-text"
          aria-label="Close modal"
        >
          <svg xmlns="http://www.w3.org/2000/svg" className="h-6 w-6" fill="none" viewBox="0 0 24 24" stroke="currentColor">
            <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M6 18L18 6M6 6l12 12" />
          </svg>
        </button>
      </div>
    </div>
  );
};

export default QRCodeModal;
