#ifndef _H_CONFIG_H_
#define _H_CONFIG_H_

/**
 * Config singleton which contains the main 
 * configuration values of the slot machine.
 *
 * @author : Pascal Marechal <paskal.marechal.gmail.com>
 * 
 * @date : 04/10/2013
 */

class Config
{
private:
	// Singleton Instance
	static Config* m_instance;
	// Number of currently used singletons
	int m_numOfSingletonRef;	

	// Number of lines in the slot machine
	int m_numberOfLines;
	// Number of symbols on one wheel
	int m_numberOfSymbols;
	// Number of wheels
	int m_numberOfWheels;
	// Error during the loading of the file ?
	bool m_loadError;

	// Main contructor
	Config();
	// Main destructor
	~Config();
	// Load config from txt file
	void LoadConfig();
public:
	
	// Get the instance of the singleton
	static Config* GetInst();
	// Delete the ref of the singleton
	void DeleteRef();
	// Get the error flag
	const bool& GetLoadErr();

	// FOR DEBUG : DISPLAY the values of the class of the config
	void DebugPrint();
};


#endif
