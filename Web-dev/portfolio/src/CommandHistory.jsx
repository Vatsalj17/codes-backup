import Welcome from './Welcome';

export default function CommandHistory({ history }) {
  return (
    <div>
      {history.map((item, index) => {
        switch (item.type) {
          case 'welcome':
            return <Welcome key={index} />;
          case 'command':
            return (
              <div key={index} className="flex items-center">
                <span className="text-green">vatsal@portfolio</span>
                <span className="text-text mx-1">:</span>
                <span className="text-blue">~</span>
                <span className="text-text mr-2">$</span>
                <p className="flex-1">{item.content}</p>
              </div>
            );
          case 'output':
            // Use dangerouslySetInnerHTML to render styled HTML content
            return (
              <div
                key={index}
                className="font-mono whitespace-pre-wrap"
                dangerouslySetInnerHTML={{ __html: item.content }}
              />
            );
          case 'error':
            return <pre key={index} className="font-mono whitespace-pre-wrap text-red">{item.content}</pre>;
          default:
            return null;
        }
      })}
    </div>
  );
}
