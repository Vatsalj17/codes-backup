import { useState, useEffect, useRef } from 'react';
import CommandHistory from './CommandHistory';
import Prompt from './Prompt';

const WS_URL = 'ws://localhost:8080';

// Helper function to create styled spans for highlighting text
const highlight = (color, text) => `<span class="text-${color}">${text}</span>`;
const bold = (text) => `<span class="font-bold">${text}</span>`;

// --- Command Definitions ---
// The execute functions now use a wider color palette, avoiding green and italics.
const commandData = {
  about: {
    description: 'Displays a short biography.',
    execute: () => [
      `Hello! I'm ${bold(highlight('mauve', 'Vatsal Jaiswal'))}, a second-year B.Tech student at GLBITM (Class of '28).`,
      `I'm deeply passionate about the low-level side of computing: ${highlight('sky', 'kernels')}, ${highlight('sky', 'device drivers')},`,
      `${highlight('sky', 'operating systems')}, ${highlight('sky', 'networking')}, and ${highlight('sky', 'compilers')}. I thrive on understanding how things`,
      'work from the silicon up.',
      `My approach is rooted in ${highlight('peach', 'logic')} and ${highlight('peach', 'mathematics')}, which I love applying to solve complex`,
      `engineering problems, especially in ${bold(highlight('red', 'C'))} and ${bold(highlight('peach', 'Rust'))}.`,
    ],
  },
  projects: {
    description: 'Lists my key projects with brief descriptions.',
    execute: () => [
      'Here are some of the projects I\'ve built:',
      `  - ${bold(highlight('blue', "vsh (Vatsal's Shell)"))}: A custom Linux shell built from scratch in C, featuring job control and command parsing.`,
      `  - ${bold(highlight('blue', 'TUI Text Editor'))}:    A simple, Vim-like text editor for the terminal, also written purely in C.`,
      `  - ${bold(highlight('blue', 'TCP Chatroom'))}:       A multi-client chat server using raw TCP sockets and POSIX threads in C.`,
      `  - ${bold(highlight('blue', 'Weather App'))}:        A command-line utility to fetch weather data using libcurl and cJSON.`,
    ],
  },
  skills: {
    description: 'Lists my technical skills and areas of interest.',
    execute: () => [
      'My skillset includes:',
      `  - ${highlight('teal', 'Languages')}:     ${bold('C (Proficient)')}, C++, Rust, Python, x86 Assembly, Verilog`,
      `  - ${highlight('teal', 'Systems')}:       Linux Kernel, OS Design, Socket Programming, Computer Networking, Docker`,
      `  - ${highlight('teal', 'Tools')}:         GDB, GNU Make, Git, Wireshark, Valgrind`,
      `  - ${highlight('teal', 'Web/DB')}:        FastAPI, HTML/CSS/JS, PostgreSQL, MongoDB`,
      `  - ${highlight('teal', 'Interests')}:     Embedded Systems (ESP32), Computer Vision (OpenCV, YOLO)`,
    ],
  },
  education: {
    description: 'Details my educational background.',
    execute: () => [
      `${bold('Bachelor of Technology (B.Tech), Computer Science')}`,
      'GL Bajaj Institute of Technology and Management (GLBITM), Greater Noida, India',
      `${highlight('sky', 'Expected Graduation: 2028')}`,
    ],
  },
  setup: {
    description: 'Describes my current hardware and software setup.',
    execute: () => [
      'I run a purpose-built setup on my Lenovo Ideapad Slim 3i:',
      `  - ${highlight('yellow', 'CPU')}:      Intel® Core™ i7-13620H (10 Cores / 16 Threads)`,
      `  - ${highlight('yellow', 'RAM')}:      16GB LPDDR5`,
      `  - ${highlight('yellow', 'Storage')}:  512GB NVMe SSD`,
      `  - ${highlight('yellow', 'OS')}:       ${bold('Arch Linux')} (w/ Zen Kernel) using the ${bold('Hyprland')} Wayland compositor`,
      'I believe in building and understanding my environment from the ground up.',
    ],
  },
  contact: {
    description: 'Shows my contact information.',
    execute: () => [
      'You can reach out to me through the following channels:',
      `  - ${highlight('maroon', 'Email')}:    vatsaljaiswal17@gmail.com`,
      `  - ${highlight('maroon', 'GitHub')}:   github.com/vatsalj17`,
      `  - ${highlight('maroon', 'LinkedIn')}: linkedin.com/in/vatsalj17`,
      'Feel free to connect!',
    ],
  },
  clear: {
    description: 'Clears the terminal history.',
    execute: ({ setHistory }) => {
      setHistory([]);
      return null;
    },
  },
};

commandData.help = {
  description: 'Displays this help message.',
  execute: () => {
    const helpLines = ['Available client-side commands:', ''];
    Object.keys(commandData)
      .sort()
      .forEach((cmd) => {
        if (commandData[cmd].description) {
          const paddedCmd = cmd.padEnd(12);
          helpLines.push(`  ${bold(highlight('blue', paddedCmd))} ${commandData[cmd].description}`);
        }
      });
    helpLines.push(
      '',
      'Any other command will be sent to the connected backend shell.'
    );
    return helpLines;
  },
};
// --- End of Command Definitions ---

export default function App() {
  const [history, setHistory] = useState([{ type: 'welcome' }]);
  const [input, setInput] = useState('');
  const [isConnected, setIsConnected] = useState(false);
  const ws = useRef(null);
  const endOfHistoryRef = useRef(null);

  useEffect(() => {
    let reconnectTimeoutId = null;
    const connect = () => {
      console.log('Attempting to connect WebSocket...');
      const socket = new WebSocket(WS_URL);

      socket.onopen = () => {
        console.log('WebSocket connected successfully.');
        setIsConnected(true);
        ws.current = socket;
      };
      socket.onmessage = (event) => {
        if (event.data !== '[EOT]') {
          setHistory((prev) => [...prev, { type: 'output', content: event.data }]);
        }
      };
      socket.onclose = () => {
        console.log('WebSocket disconnected.');
        setIsConnected(false);
        ws.current = null;
        reconnectTimeoutId = setTimeout(connect, 3000);
      };
      socket.onerror = (error) => {
        console.error('WebSocket error:', error);
        socket.close();
      };
    };
    connect();

    return () => {
      if (reconnectTimeoutId) clearTimeout(reconnectTimeoutId);
      if (ws.current) {
        ws.current.onclose = null;
        ws.current.close();
      }
    };
  }, []);

  useEffect(() => {
    endOfHistoryRef.current?.scrollIntoView({ behavior: 'smooth' });
  }, [history]);

  const handleCommand = (command) => {
    const trimmedCommand = command.trim();
    if (!trimmedCommand) return;
    setHistory((prev) => [...prev, { type: 'command', content: trimmedCommand }]);
    const [cmd] = trimmedCommand.split(' ');

    if (commandData[cmd]) {
      const output = commandData[cmd].execute({ setHistory });

      if (output) {
        if (Array.isArray(output)) {
          const outputItems = output.map((line) => ({
            type: 'output',
            content: line,
          }));
          setHistory((prev) => [...prev, ...outputItems]);
        } else {
          setHistory((prev) => [...prev, { type: 'output', content: output }]);
        }
      }
    } else {
      if (isConnected && ws.current?.readyState === WebSocket.OPEN) {
        ws.current.send(trimmedCommand);
      } else {
        setHistory((prev) => [
          ...prev,
          {
            type: 'error',
            content: `Command not found: ${trimmedCommand}. Backend is not connected.`,
          },
        ]);
      }
    }
  };

  return (
    <div
      className="min-h-screen p-4"
      onClick={() => document.getElementById('prompt-input')?.focus()}
    >
      <CommandHistory history={history} />
      <Prompt
        input={input}
        setInput={setInput}
        handleCommand={handleCommand}
        isConnected={isConnected}
      />
      <div ref={endOfHistoryRef} />
    </div>
  );
}
