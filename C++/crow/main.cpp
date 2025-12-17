#include <iostream>
#include "crow.h"
using namespace std;

int main() {
	crow::SimpleApp app;

	CROW_ROUTE(app, "/")([]() {
		return "Hello world";
	});

	CROW_ROUTE(app, "/json")
	([] {
		crow::json::wvalue x({{"message", "Hello, World!"}});
		x["message2"] = "Hello, World.. Again!";
		return x;
	});

	CROW_ROUTE(app, "/hello/<int>")
	([](int count) {
		cout << count << endl;
		return crow::response(std::to_string(count));
	});

	CROW_ROUTE(app, "/chad")([](const crow::request& req) {
		return req.url_params.get("param_name");
	});

	CROW_ROUTE(app, "/params")
	([](const crow::request& req) {
		auto name = req.url_params.get("name");
		auto age = req.url_params.get("age");

		if (!name) name = "Guest";
		if (!age) age = "0";

		return crow::response(
			"Hello " + std::string(name) + ", Age: " + std::string(age));
	});

	CROW_ROUTE(app, "/postdata").methods("POST"_method)([](const crow::request& req) {
		auto data = crow::json::load(req.body);
		if (!data)
			return crow::response(400);

		std::string name = data["name"].s();
		int age = data["age"].i();

		return crow::response("Received: " + name + " (" + std::to_string(age) + ")");
	});

	CROW_ROUTE(app, "/upload").methods("POST"_method)([](const crow::request& req) {
		std::string body = req.body;

		// 1. Find filename in Content-Disposition
		std::string filename = "uploaded_file.bin";	 // fallback
		auto fnPos = body.find("filename=\"");
		if (fnPos != std::string::npos) {
			fnPos += 10;  // move past 'filename="'
			auto endPos = body.find("\"", fnPos);
			if (endPos != std::string::npos) {
				filename = body.substr(fnPos, endPos - fnPos);
			}
		}

		// 2. Find start of file content (after headers)
		auto fileStart = body.find("\r\n\r\n");
		if (fileStart == std::string::npos) {
			return crow::response(400, "Invalid multipart format");
		}
		fileStart += 4;

		// 3. Find end (before boundary)
		auto fileEnd = body.rfind("\r\n------");
		if (fileEnd == std::string::npos) {
			return crow::response(400, "Invalid multipart format");
		}

		std::string fileData = body.substr(fileStart, fileEnd - fileStart);

		// 4. Save file with original name
		std::ofstream ofs(filename, std::ios::binary);
		ofs.write(fileData.c_str(), fileData.size());
		ofs.close();

		return crow::response(200, "File uploaded and saved as " + filename);
	});

	app.port(18080).run();
}
