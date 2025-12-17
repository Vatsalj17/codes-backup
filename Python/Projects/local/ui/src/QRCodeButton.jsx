import React, { useState } from 'react';
import QRCodeModal from './QRCodeModal';

const QRCodeButton = () => {
    const [isModalOpen, setIsModalOpen] = useState(false);

    return (
        <>
            <button
                onClick={() => setIsModalOpen(true)}
                className="fixed bottom-4 right-4 w-14 h-14 bg-crust text-teal rounded-full shadow-lg flex items-center justify-center transition-transform hover:scale-110"
                aria-label="Show QR Code"
                title="Show QR Code"
            >
                <svg xmlns="http://www.w3.org/2000/svg" className="h-7 w-7" viewBox="0 0 24 24" fill="currentColor">
                    <path d="M4 4h6v6H4V4zm8 0h6v6h-6V4zM4 14h6v6H4v-6zm8 4h2v2h-2v-2zm2-2h2v2h-2v-2zm2-2h2v2h-2v-2zm0 4h2v2h-2v-2zm-4-2h2v2h-2v-2zm-6 2h2v2H8v-2zm-2-4h2v2H6v-2zM8 8h2v2H8V8z"/>
                </svg>
            </button>
            <QRCodeModal isOpen={isModalOpen} onClose={() => setIsModalOpen(false)} />
        </>
    );
};

export default QRCodeButton;
