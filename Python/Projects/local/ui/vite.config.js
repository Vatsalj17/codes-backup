import { defineConfig } from 'vite'
import tailwindcss from '@tailwindcss/vite'
import react from '@vitejs/plugin-react'
import path from 'path' // Make sure to import the 'path' module

// https://vite.dev/config/
export default defineConfig({
  plugins: [react(),tailwindcss()],
  // Add this 'build' section
  build: {
    // This is the important part
    outDir: path.resolve(__dirname, './dist'),
    emptyOutDir: true, // This will clear the directory before building
  },
})
