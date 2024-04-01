_Task BottlingPlant {
    Printer & printer;
    NameServer & nameServer;
    unsigned int numVendingMachines;
    unsigned int maxShippedPerFlavour;
    unsigned int maxStockPerFlavour;
    unsigned int timeBetweenShipments;
	void main();
  public:
	enum Flavours { BLUES_BLACK_CHERRY, CLASSIC_CREAM_SODA, ROCK_ROOT_BEER, JAZZ_LIME, NUM_OF_FLAVOURS };	// flavours of soda
	_Event Shutdown {};					// shutdown plant
	BottlingPlant( Printer & prt, NameServer & nameServer, unsigned int numVendingMachines,
				 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
				 unsigned int timeBetweenShipments );
	void getShipment( unsigned int cargo[] );
};
