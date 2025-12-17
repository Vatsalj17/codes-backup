import React, { useState, useEffect } from 'react';

const themes = ['mocha', 'macchiato', 'frappe', 'latte'];
const themeIcons = {
  mocha: '🌙',
  macchiato: '☕',
  frappe: '🍹',
  latte: '☀️'
};


const ThemeSwitcher = () => {
  const [theme, setTheme] = useState(localStorage.getItem('theme') || 'mocha');

  useEffect(() => {
    document.documentElement.setAttribute('data-theme', theme);
    localStorage.setItem('theme', theme);
  }, [theme]);

  const cycleTheme = () => {
    const currentIndex = themes.indexOf(theme);
    const nextIndex = (currentIndex + 1) % themes.length;
    setTheme(themes[nextIndex]);
  };

  return (
    <button
      onClick={cycleTheme}
      className="fixed bottom-4 left-4 w-14 h-14 bg-crust text-text text-2xl rounded-full shadow-lg flex items-center justify-center transition-transform hover:scale-110"
      aria-label={`Switch theme. Current: ${theme}`}
      title={`Current theme: ${theme}`}
    >
      {themeIcons[theme]}
    </button>
  );
};

export default ThemeSwitcher;
