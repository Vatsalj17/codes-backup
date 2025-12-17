export default function Prompt({ input, setInput, handleCommand, isConnected }) {
  const handleKeyDown = (e) => {
    if (e.key === 'Enter') {
      e.preventDefault();
      handleCommand(input);
      setInput('');
    }
  };

  return (
    <div className="flex items-center">
      <span className={`mr-2 ${isConnected ? 'text-green' : 'text-red'}`}>●</span>
      <span className="text-green">vatsal@portfolio</span>
      <span className="text-text mx-1">:</span>
      <span className="text-blue">~</span>
      <span className="text-text mr-2">$</span>
      <input
        id="prompt-input"
        type="text"
        className="bg-transparent border-none outline-none text-text w-full"
        value={input}
        onChange={(e) => setInput(e.target.value)}
        onKeyDown={handleKeyDown}
        autoFocus
      />
    </div>
  );
}
