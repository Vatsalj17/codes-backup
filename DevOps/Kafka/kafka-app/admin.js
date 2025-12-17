const { kafka } = require("./client");

async function init() {
  const admin = kafka.admin();
  console.log("Admin connecting...");
  admin.connect();
  console.log("Adming Connection Success...");

  console.log("creating Topic");
  await admin.createTopics({
    topics: [
      {
        topic: "rider-updates",
        numPartitions: 2,
      },
      {
        topic: "seekhle-bkl",
        numPartitions: 2,
      }
    ]
  });
  console.log("Topic Created [rider-updates]");

  console.log("Disconnecting....");
  admin.disconnect();
}

init();
