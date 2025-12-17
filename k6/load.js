// import http from "k6/http"
// import { sleep } from "k6"
//
// export let options = {
//   vus: 50,
//   iteration: 1000,
// }
//
// export default function() {
//   let uniqueEmail = `user_${__VU}_${__ITER}@test.com`
//   let url = "http://127.0.0.1:8000/users"
//   let payload = JSON.stringify({
//     email: uniqueEmail,
//     password: "pass",
//   })
//   let params = {
//     Headers: { "Content-Type": "application/json" },
//   }
//   http.post(url, payload, params)
//   sleep(0.1)
// }
import http from "k6/http";

export let options = {
  scenarios: {
    load_test: {
      executor: "constant-arrival-rate",
      rate: 1000,           // 1000 requests per second
      timeUnit: "1s",       // per second
      duration: "100s",     // run for 100 seconds → 100,000 requests total
      preAllocatedVUs: 100, // pool of VUs
      maxVUs: 10000,        // scale up to 10,000 if needed
    },
  },
};

export default function () {
  let uniqueEmail = `user_${__VU}_${Date.now()}_${Math.random()
    .toString(36)
    .substring(7)}@test.com`;

  let url = "http://127.0.0.1:8000/login";
  let payload = JSON.stringify({
    email: uniqueEmail,
    password: "password123jaise_khatarnak",
  });

  let params = {
    headers: { "Content-Type": "application/json" },
  };

  http.post(url, payload, params);
}
