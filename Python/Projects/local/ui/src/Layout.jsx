import React from 'react';
import { Outlet } from 'react-router-dom';
import ThemeSwitcher from './ThemeSwitcher';
import QRCodeButton from './QRCodeButton'; // 1. Import the button

const Layout = () => {
  return (
    <>
      <Outlet /> {/* This will render either App.jsx or LiveEditor.jsx */}
      <ThemeSwitcher />
      <QRCodeButton /> {/* 2. Add the button component here */}
    </>
  );
};

export default Layout;
