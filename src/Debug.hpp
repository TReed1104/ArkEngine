#ifndef CPP_DEBUG_HPP_
#define CPP_DEBUG_HPP_

#include <iostream>
#include <fstream>
#include <string>

namespace Debug {
	class Debugger {
	public:

		// Constructors
		Debugger(const std::string& name = "", const bool& isDebuggerEnabled = false, const bool& isLoggingEnabled = false, const std::string& loggingFilePath = "") {
			this->name = name;
			this->isDebuggerEnabled = isDebuggerEnabled;
			this->isLoggingEnabled = isLoggingEnabled;
			this->loggingFilePath = loggingFilePath;
		}
		~Debugger() {
			if (outputFile != nullptr) {
				if (outputFile->is_open()) {
					outputFile->close();
				}
				delete outputFile;
			}
		}

		// Outputs
		void LogLine(const std::string& output) {
			if (isLoggingEnabled) {
				if (outputFile == nullptr) {
					outputFile = new std::ofstream();
				}
				if (!outputFile->is_open()) {
					outputFile->open("logs/" + loggingFilePath);
				}
				*(outputFile) << output << std::endl;
			}
		}
		void WriteLine(const std::string& output) {
			if (isDebuggerEnabled) {
				std::cout << output << std::endl;
				LogLine(output);
			}
		}

		// Get States
		const std::string GetName() {
			return name;
		}
		const bool GetDebuggingState() {
			return isDebuggerEnabled;
		}
		const bool GetLoggingState() {
			return isLoggingEnabled;
		}
		const std::string GetLoggingFilePath() {
			return loggingFilePath;
		}

		// Set States
		void SetName(const std::string& newName) {
			this->name = newName;
		}
		void SetDebuggingState(const bool& isEnabled) {
			this->isDebuggerEnabled = isEnabled;
		}
		void SetLoggingState(const bool& isEnabled) {
			this->isLoggingEnabled = isEnabled;
		}
		void SetLoggingFilePath(const std::string& newFilePath) {
			this->loggingFilePath = newFilePath;
		}

	private:
		// Private Variables
		std::string name;
		bool isDebuggerEnabled = false;
		bool isLoggingEnabled = false;
		std::string loggingFilePath = "";
		std::ofstream* outputFile = nullptr;

	};
};

#endif
