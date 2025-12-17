/** @type {import('tailwindcss').Config} */
export default {
  content: [
    "./index.html",
    "./src/**/*.{js,ts,jsx,tsx}",
  ],
  theme: {
    extend: {
      colors: {
        'base': 'var(--color-base)',
        'text': 'var(--color-text)',
        'mauve': 'var(--color-mauve)',
        'pink': 'var(--color-pink)',
        'green': 'var(--color-green)',
        'blue': 'var(--color-blue)',
        'red': 'var(--color-red)',
      },
      fontFamily: {
        'mono': ['"Fira Code"', 'monospace'],
      },
    },
  },
  plugins: [],
}
