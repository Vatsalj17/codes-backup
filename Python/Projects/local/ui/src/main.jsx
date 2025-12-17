import React from 'react';
import ReactDOM from 'react-dom/client';
import { createBrowserRouter, RouterProvider } from 'react-router-dom';
import App from './App';
import LiveEditor from './LiveEditor'; // We will create this next
import Layout from './Layout'; // Import the new Layout
import './index.css';

const router = createBrowserRouter([
  {
    element: <Layout />, // Use Layout as the parent for all routes
    children: [
      {
        path: '/',
        element: <App />,
      },
      {
        path: '/editor',
        element: <LiveEditor />,
      },
    ]
  }
]);

ReactDOM.createRoot(document.getElementById('root')).render(
  <React.StrictMode>
    <RouterProvider router={router} />
  </React.StrictMode>
);

