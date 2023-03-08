#include "vehicles.h"
#include "nativeFuncs.h"
#include "gta_util.h"
#include "script.h"

static const char* car_classes[] = {
	"Boats", "Comercial", "Compacts", "Coupes", "Cycles",
	"Emergency", "Helicopters", "Industrial", "Military", "Motorcycles", "Muscle",
	"OffRoad", "Planes", "Sedans", "Service", "Sports", "Sports Classics",
	"Super", "SUVs", "Trailer", "Trains", "Utility", "Vans", "DLC: Import/Export",
	"DLC: Gunrunning", "DLC: Smuggler's Run", "DLC: Doomsday Heist", "DLC: Super Sport Series",
	"DLC: After Hours", "DLC: Arena War", "DLC: Diamond Casino"
};


static const char* Import_Export[] = {
	"BLAZER5", "BOXVILLE5", "DIABLOUS", "DIABLOUS2", "COMET3", "DUNE4", "DUNE5", "ELEGY", "FCR", "FCR2", "ITALIGTB", "ITALIGTB2", "NERO", "NERO2",
	 "PENETRATOR", "PHANTOM2", "RUINER2", "SPECTER", "SPECTER2", "TECHNICAL2", "TEMPESTA", "VOLTIC2", "WASTELANDER"
};

static const char* Gunrunning[] = {
	"XA21", "CADDY3", "VAGNER", "PHANTOM3", "NIGHTSHARK", "CHEETAH2", "TORERO", "HAULER2", "TECHNICAL3", "INSURGENT3", "APC", "TAMPA3", "DUNE3",
	 "TRAILERSMALL2", "HALFTRACK", "ARDENT", "OPPRESSOR"
};

static const char* Smugglers_Run[] = {
	"ALPHAZ1", "VISIONE", "STARLING", "TULA", "HAVOK", "MICROLIGHT", "MOLOTOK", "RETINUE", "ROGUE", "HOWARD", "PYRO", "CYCLONE", "RAPIDGT3",
	 "HUNTER", "MOGUL", "BOMBUSHKA", "NOKOTA", "VIGILANTE", "SEABREEZE"
};

static const char* Doomsday_Heist[] = {
	"AKULA", "BARRAGE", "CHERNOBOG", "RAIDEN", "YOSEMITE", "DELUXO", "AVENGER", "AVENGER2", "THRUSTER", "PARIAH", "STROMBERG", "COMET4", "COMET5", "RIOT2",
	 "KHANJALI", "SC1", "VOLATOL", "HERMES", "SAVESTRA", "RIATA", "STREITER", "KAMACHO", "GT500", "Z190", "VISERIS", "AUTARCH",  "NEON", "REVOLTER", "SENTINEL3", "HUSTLER"
};

static const char* Super_Sport_Series[] = {
	"CARACARA", "CHEBUREK", "DOMINATOR3", "ELLIE", "ENTITY2", "FAGALOA", "AVENGER", "FLASHGT", "GB200", "HOTRING", "ISSI3", "JESTER3", "MICHELLI",
	 "SEASPARROW", "TEZERACT", "TAIPAN", "TYRANT"
};

static const char* After_Hours[] = {
	"BLIMP3", "FREECRAWLER", "MENACER", "OPPRESSOR2", "PATRIOT2", "SCRAMJET", "STAFFORD", "STRIKEFORCE", "SWINGER", "TERBYTE"
};

static const char* Arena_War[] = {
	"BRUISER", "BRUISER2", "BRUISER3", "BRUTUS", "BRUTUS2", "BRUTUS3", "CERBERUS", "CERBERUS2", "CERBERUS3", "CLIQUE", "DEATHBIKE", "DEATHBIKE2", "DEATHBIKE3",
	 "DEVESTE", "DEVIANT", "DOMINATOR4", "DOMINATOR5", "DOMINATOR6", "IMPALER", "IMPALER2", "IMPALER3", "IMPALER4", "IMPERATOR", "IMPERATOR2", "IMPERATOR3", "ISSI4", "ISSI5", "ISSI6",
	 "ITALIGTO", "MONSTER3", "MONSTER4", "MONSTER5", "RCBANDITO", "SCARAB", "SCARAB2", "SCARAB3", "SCHLAGEN", "SLAMVAN4", "SLAMVAN5", "SLAMVAN6", "TULIP", "VAMOS",
	 "ZR380", "ZR3802", "ZR3803"
};

static const char* Diamond_Casino[] = {
	"CARACARA2", "DYNASTY", "EMERUS",
	"GAUNTLET3", "GAUNTLET4", "HELLION", "ISSI7",
	"JUGULAR", "KRIEGER", "LOCUST", "NEBULA",
	"NEO", "NOVAK", "PARAGON", "PARAGON2",
	"PEYOTE2", "RROCKET", "S80",
	"THRAX", "ZION3", "ZORRUSSO"
};

static const char* Diamond_Casino_Heist[] = {
	"FORMULA", "FORMULA2", "FURIA", "IMORGON",
	"KOMODA", "REBLA", "STRYDER", "VSTR",
	"ASBO", "EVERON", "KANJO", "OUTLAW",
	"RETINUE2", "SUGOI", "SULTAN2",
	"VAGRANT", "YOSEMITE2", "JB7002",
	"MINITANK", "ZHABA"
};

static const char* Boats1[] = {
	"DINGHY", "DINGHY2", "DINGHY3", "JETMAX",
	"MARQUIS", "PREDATOR", "SEASHARK", "SEASHARK2", "SEASHARK3",
	"SPEEDER", "SPEEDER2", "SQUALO", "SUBMERSIBLE", "SUBMERSIBLE2",
	"SUNTRAP", "TORO", "TORO2", "TROPIC", "TROPIC2",
	"TUG"
};
static const char* Commercial1[] = {
	"BENSON", "BIFF", "HAULER", "HAULER2", "MULE", "MULE2",
	"MULE3", "MULE4", "PACKER", "PHANTOM","PHANTOM2", "PHANTOM3", "POUNDER", "POUNDER2", "STOCKADE",
	"STOCKADE3", "TERBYTE", "CERBERUS", "CERBERUS2", "CERBERUS3",
};
static const char* Compacts1[] = {
	"BLISTA", "BLISTA2", "BLISTA3", "BRIOSO", "DILETTANTE", "DILETTANTE2",
	"PANTO", "PRAIRIE", "RHAPSODY", "ISSI2", "ISSI3", "ISSI4", "ISSI5", "ISSI6", "ISSI7"
};
static const char* Coupes1[] = {
	"COGCABRIO", "EXEMPLAR", "F620", "FELON", "FELON2",
	"JACKAL", "ORACLE", "ORACLE2", "SENTINEL", "SENTINEL2",
	"WINDSOR", "WINDSOR2", "ZION", "ZION2"
};
static const char* Cycles1[] = {
	"BMX", "CRUISER", "FIXTER", "SCORCHER", "TRIBIKE",
	"TRIBIKE2", "TRIBIKE3"
};
static const char* Emergency1[] = {
	"AMBULANCE", "FBI", "FBI2", "FIRETRUK",
	"POLICE", "POLICE2", "POLICE3",
	"POLICE4", "POLICEOLD1", "POLICEOLD2", "POLICET", "POLICEB",
	"PBUS", "PRANGER", "LGUARD",
	"SHERIFF", "SHERIFF2", "RIOT", "RIOT2"
};
static const char* Helicopters1[] = {
	"ANNIHILATOR", "BUZZARD", "BUZZARD2",
	"CARGOBOB", "CARGOBOB2", "CARGOBOB3", "CARGOBOB4", "FROGGER",
	"FROGGER2", "MAVERICK", "POLMAV", "SAVAGE", "SKYLIFT",
	"SUPERVOLITO", "SUPERVOLITO2", "SWIFT", "SWIFT2", "VALKYRIE",
	"VALKYRIE2", "VOLATUS", "HAVOK", "MICROLIGHT", "HUNTER", "AKULA",
	"AVENGER", "AVENGER2", "SEASPARROW"
};
static const char* Industrial1[] = {
	"BULLDOZER", "CUTTER", "DUMP", "FLATBED", "GUARDIAN",
	"HANDLER", "MIXER", "MIXER2", "RUBBLE", "TIPTRUCK",
	"TIPTRUCK2"
};
static const char* Military1[] = {
	"BARRACKS", "BARRACKS2", "CRUSADER", "RHINO",  "APC",
	"HALFTRACK", "BARRAGE", "CHERNOBOG", "KHANJALI", "SCARAB", "SCARAB2", "SCARAB3",
	"THRUSTER"
};
static const char* Motorcycles1[] = {
	"AKUMA", "AVARUS", "BAGGER", "BATI", "BATI2",
	"BF400", "CARBONRS", "CHIMERA", "CLIFFHANGER", "DAEMON",
	"DAEMON2", "DEFILER", "DOUBLE", "ENDURO", "ESSKEY",
	"FAGGIO", "FAGGIO2", "FAGGIO3", "GARGOYLE", "HAKUCHOU",
	"HAKUCHOU2", "HEXER", "INNOVATION", "LECTRO", "MANCHEZ",
	"NEMESIS", "NIGHTBLADE", "PCJ", "RATBIKE", "RUFFIAN",
	"SANCHEZ", "SANCHEZ2", "SANCTUS", "SHOTARO", "SOVEREIGN",
	"THRUST", "VADER", "VINDICATOR", "VORTEX", "WOLFSBANE",
	"ZOMBIEA", "ZOMBIEB", "DIABLOUS", "DIABLOUS2", "FCR",
	"FCR2", "OPPRESSOR", "OPPRESSOR2", "DEATHBIKE", "DEATHBIKE2", "DEATHBIKE3", "RROCKET"

};
static const char* Muscle1[] = {
	"BLADE", "BUCCANEER", "BUCCANEER2", "CHINO", "CHINO2",
	"COQUETTE3", "DOMINATOR", "DOMINATOR2", "DOMINATOR3", "DOMINATOR4", "DOMINATOR5", "DOMINATOR6", "DUKES", "DUKES2",
	"GAUNTLET", "GAUNTLET2", "FACTION", "FACTION2", "FACTION3",
	"HOTKNIFE", "LURCHER", "MOONBEAM", "MOONBEAM2", "NIGHTSHADE",
	"PHOENIX", "PICADOR", "RATLOADER", "RATLOADER2", "RUINER", "RUINER2", "RUINER3",
	"SABREGT", "SABREGT2", "SLAMVAN", "SLAMVAN2", "SLAMVAN3",
	"STALION", "STALION2", "TAMPA", "TAMPA3", "VIGERO", "VIRGO",
	"VIRGO2", "VIRGO3", "VOODOO", "VOODOO2", "ELLIE",
	"CLIQUE", "DEVIANT", "IMPALER", "IMPALER2", "IMPALER3", "IMPALER4",
	"IMPERATOR", "IMPERATOR2", "IMPERATOR3", "SLAMVAN4", "SLAMVAN5", "SLAMVAN6",
	"TULIP", "VAMOS","GAUNTLET3", "GAUNTLET4", "YOSEMITE"
};
static const char* OffRoad1[] = {
	"BFINJECTION", "BIFTA", "BLAZER", "BLAZER2", "BLAZER3",
	"BLAZER4", "BLAZER5", "BODHI2", "BRAWLER", "DLOADER", "DUBSTA3",
	"DUNE", "DUNE2", "DUNE3", "DUNE4", "DUNE5", "INSURGENT", "INSURGENT2", "INSURGENT3", "KALAHARI",
	"MARSHALL", "MESA3", "MONSTER", "MONSTER3", "MONSTER4", "MONSTER5", "RANCHERXL", "RANCHERXL2",
	"REBEL", "REBEL2", "SANDKING", "SANDKING2", "TECHNICAL", "TECHNICAL2", "TECHNICAL3", "NIGHTSHARK",
	"TROPHYTRUCK", "TROPHYTRUCK2",
	"COMET4", "RIATA", "KAMACHO", "CARACARA","CARACARA2", "FREECRAWLER", "MENACER",
	"BRUISER", "BRUISER2", "BRUISER3", "BRUTUS", "BRUTUS2", "BRUTUS3", "RCBANDITO", "HELLION"

};
static const char* Planes1[] = {
	"BESRA", "BLIMP", "BLIMP2", "BLIMP3", "CARGOPLANE", "CUBAN800", "DODO", "DUSTER",
	"HYDRA", "JET", "LAZER", "LUXOR", "LUXOR2",
	"MAMMATUS", "MILJET", "NIMBUS", "SHAMAL", "STUNT",
	"TITAN", "VELUM", "VELUM2", "VESTRA", "ALPHAZ1",
	"STARLING", "TULA", "MOLOTOK", "ROGUE", "HOWARD", "PYRO",
	"MOGUL", "BOMBUSHKA", "NOKOTA", "SEABREEZE", "VOLATOL",
	"STRIKEFORCE"
};
static const char* Sedans1[] = {
	"ASEA", "ASEA2", "ASTEROPE", "COG55", "COG552",
	"COGNOSCENTI", "COGNOSCENTI2", "EMPEROR", "EMPEROR2", "EMPEROR3",
	"FUGITIVE", "GLENDALE", "INGOT", "INTRUDER", "LIMO2",
	"PREMIER", "PRIMO", "PRIMO2", "REGINA", "ROMERO",
	"SCHAFTER2", "SCHAFTER5", "SCHAFTER6", "STANIER", "STRATUM",
	"STRETCH", "SUPERD", "SURGE", "TAILGATER", "WARRENER",
	"WASHINGTON", "REVOLTER", "STAFFORD"
};
static const char* Service1[] = {
	"AIRBUS", "BRICKADE", "BUS", "PBUS2", "COACH", "RALLYTRUCK",
	"RENTALBUS", "TAXI", "TOURBUS", "TRASH", "TRASH2",
	"WASTELANDER"
};
static const char* Sports1[] = {
	"ALPHA", "BANSHEE", "BESTIAGTS",
	"BUFFALO", "BUFFALO2", "BUFFALO3", "CARBONIZZARE", "COMET2",  "COMET3", "COMET5",
	"COQUETTE", "ELEGY", "ELEGY2", "FELTZER2", "FUROREGT", "FUSILADE",
	"FUTO", "JESTER", "JESTER2", "JESTER3", "KHAMELION", "KURUMA",
	"KURUMA2", "LYNX", "MASSACRO", "MASSACRO2", "NINEF",
	"NINEF2", "OMNIS", "PENUMBRA", "RAPIDGT", "RAPIDGT2", "RAPIDGT3",
	"RAPTOR", "SCHAFTER3", "SCHAFTER4", "SCHWARZER", "SEVEN70", "STREITER",
	"SULTAN", "SURANO", "SPECTER", "SPECTER2", "TAMPA2", "TROPOS", "VERLIERER2",
	"RUSTON", "RAIDEN", "PARIAH",  "NEON", "FLASHGT", "GB200",
	"HOTRING", "SCHLAGEN", "ZR380", "ZR3802", "ZR3803", "JUGULAR", "LOCUST", "NEBULA",
	"PARAGON", "PARAGON2"
};
static const char* SportsClassics1[] = {
	"BTYPE", "BTYPE2", "BTYPE3", "CASCO", "COQUETTE2",
	"FELTZER3", "JB700", "MAMBA", "MANANA", "MONROE",
	"PEYOTE", "PEYOTE2", "PIGALLE", "STINGER", "STINGERGT", "CHEETAH2", "TORERO", "TORNADO",
	"TORNADO2", "TORNADO3", "TORNADO4", "TORNADO5", "TORNADO6", "ZION3", "RETINUE", "SAVESTRA",
	"ZTYPE", "INFERNUS2", "TURISMO2", "DELUXO", "STROMBERG", "ARDENT",
	"HERMES", "GT500", "Z190", "VISERIS", "SENTINEL3", "HUSTLER", "CHEBUREK",
	"MICHELLI", "FAGALOA", "SWINGER", "DYNASTY"

};
static const char* Super1[] = {
	"ADDER", "BANSHEE2", "BULLET", "CHEETAH", "ENTITYXF",
	"FMJ", "SHEAVA", "INFERNUS", "NERO", "NERO2","OSIRIS", "LE7B",
	"ITALIGTB", "ITALIGTB2", "PFISTER811", "PROTOTIPO", "REAPER", "SULTANRS", "T20",
	"TEMPESTA", "TURISMOR", "TYRUS", "VACCA", "VOLTIC", "VOLTIC2", "ZENTORNO", "PENETRATOR", "GP1",
	"XA21", "VAGNER", "VIGILANTE", "VISIONE", "CYCLONE", "SC1", "AUTARCH", "ENTITY2",
	"TEZERACT", "TAIPAN", "TYRANT", "SCRAMJET", "DEVESTE", "ITALIGTO", "EMERUS", "KRIEGER",
	 "S80","THRAX", "ZORRUSSO"
};
static const char* SUVs1[] = {
	"BALLER", "BALLER2", "BALLER3", "BALLER4", "BALLER5",
	"BALLER6", "BJXL", "CAVALCADE", "CAVALCADE2", "CONTENDER",
	"DUBSTA", "DUBSTA2", "FQ2", "GRANGER", "GRESLEY",
	"HABANERO", "HUNTLEY", "LANDSTALKER", "MESA", "MESA2",
	"PATRIOT", "PATRIOT2", "RADI", "ROCOTO", "SEMINOLE", "SERRANO",
	"XLS", "XLS2", "NOVAK"
};
static const char* Trailer1[] = {
	"ARMYTANKER", "ARMYTRAILER", "ARMYTRAILER2", "BALETRAILER", "BOATTRAILER",
	"CABLECAR","DOCKTRAILER", "GRAINTRAILER", "PROPTRAILER", "RAKETRAILER",
	"TR2", "TR3", "TR4", "TRFLAT", "TVTrailer", "Tanker", "Tanker2", "TrailerLogs",
	"TrailerSmall", "TRAILERSMALL2", "Trailers", "Trailers2", "Trailers3"
};
static const char* Trains1[] = {
	"FREIGHT", "FREIGHTCAR", "FREIGHTCONT1", "FREIGHTCONT2",
	"FREIGHTGRAIN", "METROTRAIN", "TANKERCAR"
};
static const char* Utility1[] = {
	"AIRTUG", "CADDY", "CADDY2", "CADDY3", "DOCKTUG", "FORKLIFT",
	"MOWER", "RIPLEY", "SADLER", "SADLER2", "SCRAP",
	"TOWTRUCK", "TOWTRUCK2", "TRACTOR", "TRACTOR2", "TRACTOR3",
	"UTILLITRUCK", "UTILLITRUCK2", "UTILLITRUCK3"
};
static const char* Vans1[] = {
	"BISON", "BISON2", "BISON3", "BOBCATXL", "BOXVILLE",
	"BOXVILLE2", "BOXVILLE3", "BOXVILLE4", "BURRITO", "BURRITO2",
	"BURRITO3", "BURRITO4", "BURRITO5", "CAMPER", "GBURRITO",
	"GBURRITO2", "JOURNEY", "MINIVAN", "MINIVAN2", "PARADISE",
	"PONY", "PONY2", "RUMPO", "RUMPO2", "RUMPO3",
	"SPEEDO", "SPEEDO2", "SPEEDO4", "SURFER", "SURFER2", "TACO",
	"YOUGA", "YOUGA2"
};

std::string getModCategoryName(int i)
{
	switch (i)
	{
	case 0:
		return "Spoiler";
	case 1:
		return "Front Bumper";
	case 2:
		return "Rear Bumper";
	case 3:
		return "Side Skirts";
	case 4:
		return "Exhaust";
	case 5:
		return "Rollcage";
	case 6:
		return "Grille";
	case 7:
		return "Bonnet";
	case 8:
		return "Fenders and Arches";
	case 9:
		return "Fenders";
	case 10:
		return "Roof";
	case 11:
		return "Engine";
	case 12:
		return "Brakes";
	case 13:
		return "Transmission";
	case 14:
		return "Horn";
	case 15:
		return "Suspension";
	case 16:
		return "Armor";
	case 22:
		return "Headlights";
	case 23:
		return "Wheels"; // front
		case 24:
		return "Wheels2"; // rear
	case 25:
		return "Plate Holders";
	case 26:
		return "Vanity Plates";
	case 27:
		return "Interior Trim";
	case 28:
		return "Ornaments";
	case 29:
		return "Interior Dash";
	case 30:
		return "Dials";
	case 31:
		return "Door Speakers";
	case 32:
		return "Leather Seats";
	case 33:
		return "Steering Wheels";
	case 34:
		return "Column Shifters";
	case 35:
		return "Plaques";
	case 36:
		return "ICE";
	case 37:
		return "Speakers";
	case 38:
		return "Hydraulics";
	case 39:
		return "Engine Block";
	case 40:
		return "Air Filters";
	case 41:
		return "Strut Braces";
	case 42:
		return "Arch Covers";
	case 43:
		return "Aerials";
	case 44:
		return "Exterior Trim";
	case 45:
		return "Tank";
	case 46:
		return "Windows";
	case 48:
		return "Livery";
		/*case SPECIAL_ID_FOR_WHEEL_CATEGORY:
			return "Wheel Category";
		case SPECIAL_ID_FOR_WHEEL_SELECTION:
			return "Wheel Choice";
		case SPECIAL_ID_FOR_WINDOW_TINT:
			return "Window Tint";
		case SPECIAL_ID_FOR_LICENSE_PLATES:
			return "License Plates";*/
	default:
		return std::to_string(i);
	}
}

std::string getHornTitle(int index)
{
	if (index == 0)
	{
		return "Truck Horn";
	}
	else if (index == 1)
	{
		return "Cop Horn";
	}
	else if (index == 2)
	{
		return "Clown Horn";
	}
	else if (index == 3)
	{
		return "Musical Horn 1";
	}
	else if (index == 4)
	{
		return "Musical Horn 2";
	}
	else if (index == 5)
	{
		return "Musical Horn 3";
	}
	else if (index == 6)
	{
		return "Musical Horn 4";
	}
	else if (index == 7)
	{
		return "Musical Horn 5";
	}
	else if (index == 8)
	{
		return "Sad Trombone";
	}
	else if (index == 9)
	{
		return "Classical Horn 1";
	}
	else if (index == 10)
	{
		return "Classical Horn 2";
	}
	else if (index == 11)
	{
		return "Classical Horn 3";
	}
	else if (index == 12)
	{
		return "Classical Horn 4";
	}
	else if (index == 13)
	{
		return "Classical Horn 5";
	}
	else if (index == 14)
	{
		return "Classical Horn 6";
	}
	else if (index == 15)
	{
		return "Classical Horn 7";
	}
	else if (index == 16)
	{
		return "Scale - Do";
	}
	else if (index == 17)
	{
		return "Scale - Re";
	}
	else if (index == 18)
	{
		return "Scale - Mi";
	}
	else if (index == 19)
	{
		return "Scale - Fa";
	}
	else if (index == 20)
	{
		return "Scale - Sol";
	}
	else if (index == 21)
	{
		return "Scale - La";
	}
	else if (index == 22)
	{
		return "Scale - Ti";
	}
	else if (index == 23)
	{
		return "Scale - Do";
	}
	else if (index == 24)
	{
		return "Jazz Horn 1";
	}
	else if (index == 25)
	{
		return "Jazz Horn 2";
	}
	else if (index == 26)
	{
		return "Jazz Horn 3";
	}
	else if (index == 27)
	{
		return "Jazz Horn Loop";
	}
	else if (index == 28)
	{
		return "Star Spangled Banner 1";
	}
	else if (index == 29)
	{
		return "Star Spangled Banner 2";
	}
	else if (index == 30)
	{
		return "Star Spangled Banner 3";
	}
	else if (index == 31)
	{
		return "Star Spangled Banner 4";
	}
	else if (index == 32)
	{
		return "Classical Horn 8 Loop";
	}
	else if (index == 33)
	{
		return "Classical Horn 9 Loop";
	}
	else if (index == 34)
	{
		return "Classical Horn 10 Loop";
	}
	else if (index == 35)
	{
		return "Classical Horn 8";
	}
	else if (index == 36)
	{
		return "Classical Horn 9";
	}
	else if (index == 37)
	{
		return "Classical Horn 10";
	}
	else if (index == 38)
	{
		return "Funeral Loop";
	}
	else if (index == 39)
	{
		return "Funeral";
	}
	else if (index == 40)
	{
		return "Spooky Loop";
	}
	else if (index == 41)
	{
		return "Spooky";
	}
	else if (index == 42)
	{
		return "San Andreas Loop";
	}
	else if (index == 43)
	{
		return "San Andreas";
	}
	else if (index == 44)
	{
		return "Liberty City Loop";
	}
	else if (index == 45)
	{
		return "Liberty City";
	}
	/*	else if (index == 46)
		{
			return "Festive 1 Loop";
		}
		else if (index == 47)
		{
			return "Festive 1";
		}
		else if (index == 48)
		{
			return "Festive 2 Loop";
		}
		else if (index == 49)
		{
			return "Festive 2";
		}
		else if (index == 50)
		{
			return "Festive 3 Loop";
		}
		else if (index == 51)
		{
			return "Festive 3";
		}
	*/
	return "Unknown Horn";
}

std::string getNormalItemTitle(Vehicle veh, int category, int index)
{
	//Engine stuff is EMS Upgrade, Level 1-4
	//Brakes/trans are stock, street, sports, race
	//Susp is stock,lowered,street,sport,competition
	//Armor is none, 20, 40, 60, 80, 100%

	std::string modItemNameStr;

	if (index == -1)
	{
		if (category == 16)
		{
			modItemNameStr = "No Armor";
		}
		else
		{
			std::ostringstream ss;
			ss << "Stock " << getModCategoryName(category);
			modItemNameStr = ss.str();
		}
	}
	else if (category == 11) //Engine
	{
		std::ostringstream ss;
		ss << "EMS Upgrade, Level " << (index + 1);
		modItemNameStr = ss.str();
	}
	else if (category == 12 || category == 13) //brakes, trans
	{
		std::ostringstream ss;
		ss << BRAKES_AND_TRANS_PREFIXES[index];
		if (category == 12)
		{
			ss << " Brakes";
		}
		else
		{
			ss << " Transmission";
		}
		modItemNameStr = ss.str();
	}
	else if (category == 14) //horn
	{
		modItemNameStr = getHornTitle(index);
	}
	else if (category == 15) //suspension
	{
		std::ostringstream ss;
		ss << SUSP_PREFIXES[index] << " Suspension";
		modItemNameStr = ss.str();
	}
	else if (category == 16) //Armor
	{
		std::ostringstream ss;
		ss << ((index + 1) * 20) << "% Armor";
		modItemNameStr = ss.str();
	}
	else
	{
		const char* modItemNameChr = VEHICLE::GET_MOD_TEXT_LABEL(veh, category, index);
		bool foundName = false;
		if (modItemNameChr != NULL && strlen(modItemNameChr) > 0)
		{
			const char* modItemNameTxt = UI::_GET_LABEL_TEXT(modItemNameChr);
			if (modItemNameTxt != NULL)
			{
				modItemNameStr = std::string(modItemNameTxt) + "##" + std::to_string(index);
				foundName = true;
			}
		}

		if (!foundName)
		{
			std::ostringstream ss;
			ss << getModCategoryName(category) << " Item " << (index + 1);
			modItemNameStr = ss.str();
		}
	}

	return modItemNameStr;
}


void Vehicles::initialize()
{
	std::vector<std::string> buffer;

	{
		VehicleClass vehClass;
		vehClass.className = "Boats";
		for (const char* str : Boats1)
		{
			std::string tmp(str);
			buffer.push_back(tmp);
			std::sort(buffer.begin(), buffer.end());
		}
		for (std::string str : buffer)
		{
			VehiclePack pack;
			pack.name = str.c_str();
			pack.hash = rage::joaat(pack.name);
			pack.labelText = UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(pack.hash));
			vehClass.vehicles.push_back(pack);
		}
		classes.push_back(vehClass);
		buffer.clear();
	}

	{
		VehicleClass vehClass;
		vehClass.className = "Commercial";
		for (const char* str : Commercial1)
		{
			std::string tmp(str);
			buffer.push_back(tmp);
			std::sort(buffer.begin(), buffer.end());
		}
		for (std::string str : buffer)
		{
			VehiclePack pack;
			pack.name = str.c_str();
			pack.hash = rage::joaat(pack.name);
			pack.labelText = UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(pack.hash));
			vehClass.vehicles.push_back(pack);
		}
		classes.push_back(vehClass);
		buffer.clear();
	}

	{
		VehicleClass vehClass;
		vehClass.className = "Compacts";
		for (const char* str : Compacts1)
		{
			std::string tmp(str);
			buffer.push_back(tmp);
			std::sort(buffer.begin(), buffer.end());
		}
		for (std::string str : buffer)
		{
			VehiclePack pack;
			pack.name = str.c_str();
			pack.hash = rage::joaat(pack.name);
			pack.labelText = UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(pack.hash));
			vehClass.vehicles.push_back(pack);
		}
		classes.push_back(vehClass);
		buffer.clear();
	}

	{
		VehicleClass vehClass;
		vehClass.className = "Coupes";
		for (const char* str : Coupes1)
		{
			std::string tmp(str);
			buffer.push_back(tmp);
			std::sort(buffer.begin(), buffer.end());
		}
		for (std::string str : buffer)
		{
			VehiclePack pack;
			pack.name = str.c_str();
			pack.hash = rage::joaat(pack.name);
			pack.labelText = UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(pack.hash));
			vehClass.vehicles.push_back(pack);
		}
		classes.push_back(vehClass);
		buffer.clear();
	}

	{
		VehicleClass vehClass;
		vehClass.className = "Cycles";
		for (const char* str : Cycles1)
		{
			std::string tmp(str);
			buffer.push_back(tmp);
			std::sort(buffer.begin(), buffer.end());
		}
		for (std::string str : buffer)
		{
			VehiclePack pack;
			pack.name = str.c_str();
			pack.hash = rage::joaat(pack.name);
			pack.labelText = UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(pack.hash));
			vehClass.vehicles.push_back(pack);
		}
		classes.push_back(vehClass);
		buffer.clear();
	}

	{
		VehicleClass vehClass;
		vehClass.className = "Emergency";
		for (const char* str : Emergency1)
		{
			std::string tmp(str);
			buffer.push_back(tmp);
			std::sort(buffer.begin(), buffer.end());
		}
		for (std::string str : buffer)
		{
			VehiclePack pack;
			pack.name = str.c_str();
			pack.hash = rage::joaat(pack.name);
			pack.labelText = UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(pack.hash));
			vehClass.vehicles.push_back(pack);
		}
		classes.push_back(vehClass);
		buffer.clear();
	}

	{
		VehicleClass vehClass;
		vehClass.className = "Helicopters";
		for (const char* str : Helicopters1)
		{
			std::string tmp(str);
			buffer.push_back(tmp);
			std::sort(buffer.begin(), buffer.end());
		}
		for (std::string str : buffer)
		{
			VehiclePack pack;
			pack.name = str.c_str();
			pack.hash = rage::joaat(pack.name);
			pack.labelText = UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(pack.hash));
			vehClass.vehicles.push_back(pack);
		}
		classes.push_back(vehClass);
		buffer.clear();
	}

	{
		VehicleClass vehClass;
		vehClass.className = "Industrial";
		for (const char* str : Industrial1)
		{
			std::string tmp(str);
			buffer.push_back(tmp);
			std::sort(buffer.begin(), buffer.end());
		}
		for (std::string str : buffer)
		{
			VehiclePack pack;
			pack.name = str.c_str();
			pack.hash = rage::joaat(pack.name);
			pack.labelText = UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(pack.hash));
			vehClass.vehicles.push_back(pack);
		}
		classes.push_back(vehClass);
		buffer.clear();
	}

	{
		VehicleClass vehClass;
		vehClass.className = "Military";
		for (const char* str : Military1)
		{
			std::string tmp(str);
			buffer.push_back(tmp);
			std::sort(buffer.begin(), buffer.end());
		}
		for (std::string str : buffer)
		{
			VehiclePack pack;
			pack.name = str.c_str();
			pack.hash = rage::joaat(pack.name);
			pack.labelText = UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(pack.hash));
			vehClass.vehicles.push_back(pack);
		}
		classes.push_back(vehClass);
		buffer.clear();
	}

	{
		VehicleClass vehClass;
		vehClass.className = "Motorcycles";
		for (const char* str : Motorcycles1)
		{
			std::string tmp(str);
			buffer.push_back(tmp);
			std::sort(buffer.begin(), buffer.end());
		}
		for (std::string str : buffer)
		{
			VehiclePack pack;
			pack.name = str.c_str();
			pack.hash = rage::joaat(pack.name);
			pack.labelText = UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(pack.hash));
			vehClass.vehicles.push_back(pack);
		}
		classes.push_back(vehClass);
		buffer.clear();
	}

	{
		VehicleClass vehClass;
		vehClass.className = "Muscle";
		for (const char* str : Muscle1)
		{
			std::string tmp(str);
			buffer.push_back(tmp);
			std::sort(buffer.begin(), buffer.end());
		}
		for (std::string str : buffer)
		{
			VehiclePack pack;
			pack.name = str.c_str();
			pack.hash = rage::joaat(pack.name);
			pack.labelText = UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(pack.hash));
			vehClass.vehicles.push_back(pack);
		}
		classes.push_back(vehClass);
		buffer.clear();
	}

	{
		VehicleClass vehClass;
		vehClass.className = "Off Road";
		for (const char* str : OffRoad1)
		{
			std::string tmp(str);
			buffer.push_back(tmp);
			std::sort(buffer.begin(), buffer.end());
		}
		for (std::string str : buffer)
		{
			VehiclePack pack;
			pack.name = str.c_str();
			pack.hash = rage::joaat(pack.name);
			pack.labelText = UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(pack.hash));
			vehClass.vehicles.push_back(pack);
		}
		classes.push_back(vehClass);
		buffer.clear();
	}

	{
		VehicleClass vehClass;
		vehClass.className = "Planes";
		for (const char* str : Planes1)
		{
			std::string tmp(str);
			buffer.push_back(tmp);
			std::sort(buffer.begin(), buffer.end());
		}
		for (std::string str : buffer)
		{
			VehiclePack pack;
			pack.name = str.c_str();
			pack.hash = rage::joaat(pack.name);
			pack.labelText = UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(pack.hash));
			vehClass.vehicles.push_back(pack);
		}
		classes.push_back(vehClass);
		buffer.clear();
	}

	{
		VehicleClass vehClass;
		vehClass.className = "Sedans";
		for (const char* str : Sedans1)
		{
			std::string tmp(str);
			buffer.push_back(tmp);
			std::sort(buffer.begin(), buffer.end());
		}
		for (std::string str : buffer)
		{
			VehiclePack pack;
			pack.name = str.c_str();
			pack.hash = rage::joaat(pack.name);
			pack.labelText = UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(pack.hash));
			vehClass.vehicles.push_back(pack);
		}
		classes.push_back(vehClass);
		buffer.clear();
	}

	{
		VehicleClass vehClass;
		vehClass.className = "Service";
		for (const char* str : Service1)
		{
			std::string tmp(str);
			buffer.push_back(tmp);
			std::sort(buffer.begin(), buffer.end());
		}
		for (std::string str : buffer)
		{
			VehiclePack pack;
			pack.name = str.c_str();
			pack.hash = rage::joaat(pack.name);
			pack.labelText = UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(pack.hash));
			vehClass.vehicles.push_back(pack);
		}
		classes.push_back(vehClass);
		buffer.clear();
	}

	{
		VehicleClass vehClass;
		vehClass.className = "Sports";
		for (const char* str : Sports1)
		{
			std::string tmp(str);
			buffer.push_back(tmp);
			std::sort(buffer.begin(), buffer.end());
		}
		for (std::string str : buffer)
		{
			VehiclePack pack;
			pack.name = str.c_str();
			pack.hash = rage::joaat(pack.name);
			pack.labelText = UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(pack.hash));
			vehClass.vehicles.push_back(pack);
		}
		classes.push_back(vehClass);
		buffer.clear();
	}

	{
		VehicleClass vehClass;
		vehClass.className = "Sports Classics";
		for (const char* str : SportsClassics1)
		{
			std::string tmp(str);
			buffer.push_back(tmp);
			std::sort(buffer.begin(), buffer.end());
		}
		for (std::string str : buffer)
		{
			VehiclePack pack;
			pack.name = str.c_str();
			pack.hash = rage::joaat(pack.name);
			pack.labelText = UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(pack.hash));
			vehClass.vehicles.push_back(pack);
		}
		classes.push_back(vehClass);
		buffer.clear();
	}

	{
		VehicleClass vehClass;
		vehClass.className = "Super";
		for (const char* str : Super1)
		{
			std::string tmp(str);
			buffer.push_back(tmp);
			std::sort(buffer.begin(), buffer.end());
		}
		for (std::string str : buffer)
		{
			VehiclePack pack;
			pack.name = str.c_str();
			pack.hash = rage::joaat(pack.name);
			pack.labelText = UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(pack.hash));
			vehClass.vehicles.push_back(pack);
		}
		classes.push_back(vehClass);
		buffer.clear();
	}

	{
		VehicleClass vehClass;
		vehClass.className = "SUVs";
		for (const char* str : SUVs1)
		{
			std::string tmp(str);
			buffer.push_back(tmp);
			std::sort(buffer.begin(), buffer.end());
		}
		for (std::string str : buffer)
		{
			VehiclePack pack;
			pack.name = str.c_str();
			pack.hash = rage::joaat(pack.name);
			pack.labelText = UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(pack.hash));
			vehClass.vehicles.push_back(pack);
		}
		classes.push_back(vehClass);
		buffer.clear();
	}

	{
		VehicleClass vehClass;
		vehClass.className = "Trailer";
		for (const char* str : Trailer1)
		{
			std::string tmp(str);
			buffer.push_back(tmp);
			std::sort(buffer.begin(), buffer.end());
		}
		for (std::string str : buffer)
		{
			VehiclePack pack;
			pack.name = str.c_str();
			pack.hash = rage::joaat(pack.name);
			pack.labelText = UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(pack.hash));
			vehClass.vehicles.push_back(pack);
		}
		classes.push_back(vehClass);
		buffer.clear();
	}

	{
		VehicleClass vehClass;
		vehClass.className = "Trains";
		for (const char* str : Trains1)
		{
			std::string tmp(str);
			buffer.push_back(tmp);
			std::sort(buffer.begin(), buffer.end());
		}
		for (std::string str : buffer)
		{
			VehiclePack pack;
			pack.name = str.c_str();
			pack.hash = rage::joaat(pack.name);
			pack.labelText = UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(pack.hash));
			vehClass.vehicles.push_back(pack);
		}
		classes.push_back(vehClass);
		buffer.clear();
	}

	{
		VehicleClass vehClass;
		vehClass.className = "Utility";
		for (const char* str : Utility1)
		{
			std::string tmp(str);
			buffer.push_back(tmp);
			std::sort(buffer.begin(), buffer.end());
		}
		for (std::string str : buffer)
		{
			VehiclePack pack;
			pack.name = str.c_str();
			pack.hash = rage::joaat(pack.name);
			pack.labelText = UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(pack.hash));
			vehClass.vehicles.push_back(pack);
		}
		classes.push_back(vehClass);
		buffer.clear();
	}

	{
		VehicleClass vehClass;
		vehClass.className = "Vans";
		for (const char* str : Vans1)
		{
			std::string tmp(str);
			buffer.push_back(tmp);
			std::sort(buffer.begin(), buffer.end());
		}
		for (std::string str : buffer)
		{
			VehiclePack pack;
			pack.name = str.c_str();
			pack.hash = rage::joaat(pack.name);
			pack.labelText = UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(pack.hash));
			vehClass.vehicles.push_back(pack);
		}
		classes.push_back(vehClass);
		buffer.clear();
	}

	{
		VehicleClass vehClass;
		vehClass.className = "Import Export";
		for (const char* str : Import_Export)
		{
			std::string tmp(str);
			buffer.push_back(tmp);
			std::sort(buffer.begin(), buffer.end());
		}
		for (std::string str : buffer)
		{
			VehiclePack pack;
			pack.name = str.c_str();
			pack.hash = rage::joaat(pack.name);
			pack.labelText = UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(pack.hash));
			vehClass.vehicles.push_back(pack);
		}
		classes.push_back(vehClass);
		buffer.clear();
	}

	{
		VehicleClass vehClass;
		vehClass.className = "Gunrunning";
		for (const char* str : Gunrunning)
		{
			std::string tmp(str);
			buffer.push_back(tmp);
			std::sort(buffer.begin(), buffer.end());
		}
		for (std::string str : buffer)
		{
			VehiclePack pack;
			pack.name = str.c_str();
			pack.hash = rage::joaat(pack.name);
			pack.labelText = UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(pack.hash));
			vehClass.vehicles.push_back(pack);
		}
		classes.push_back(vehClass);
		buffer.clear();
	}

	{
		VehicleClass vehClass;
		vehClass.className = "Smugglers Run";
		for (const char* str : Smugglers_Run)
		{
			std::string tmp(str);
			buffer.push_back(tmp);
			std::sort(buffer.begin(), buffer.end());
		}
		for (std::string str : buffer)
		{
			VehiclePack pack;
			pack.name = str.c_str();
			pack.hash = rage::joaat(pack.name);
			pack.labelText = UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(pack.hash));
			vehClass.vehicles.push_back(pack);
		}
		classes.push_back(vehClass);
		buffer.clear();
	}

	{
		VehicleClass vehClass;
		vehClass.className = "Doomsday Heist";
		for (const char* str : Doomsday_Heist)
		{
			std::string tmp(str);
			buffer.push_back(tmp);
			std::sort(buffer.begin(), buffer.end());
		}
		for (std::string str : buffer)
		{
			VehiclePack pack;
			pack.name = str.c_str();
			pack.hash = rage::joaat(pack.name);
			pack.labelText = UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(pack.hash));
			vehClass.vehicles.push_back(pack);
		}
		classes.push_back(vehClass);
		buffer.clear();
	}

	{
		VehicleClass vehClass;
		vehClass.className = "Super Sport Series";
		for (const char* str : Super_Sport_Series)
		{
			std::string tmp(str);
			buffer.push_back(tmp);
			std::sort(buffer.begin(), buffer.end());
		}
		for (std::string str : buffer)
		{
			VehiclePack pack;
			pack.name = str.c_str();
			pack.hash = rage::joaat(pack.name);
			pack.labelText = UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(pack.hash));
			vehClass.vehicles.push_back(pack);
		}
		classes.push_back(vehClass);
		buffer.clear();
	}

	{
		VehicleClass vehClass;
		vehClass.className = "After Hours";
		for (const char* str : After_Hours)
		{
			std::string tmp(str);
			buffer.push_back(tmp);
			std::sort(buffer.begin(), buffer.end());
		}
		for (std::string str : buffer)
		{
			VehiclePack pack;
			pack.name = str.c_str();
			pack.hash = rage::joaat(pack.name);
			pack.labelText = UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(pack.hash));
			vehClass.vehicles.push_back(pack);
		}
		classes.push_back(vehClass);
		buffer.clear();
	}

	{
		VehicleClass vehClass;
		vehClass.className = "Arena War";
		for (const char* str : Arena_War)
		{
			std::string tmp(str);
			buffer.push_back(tmp);
			std::sort(buffer.begin(), buffer.end());
		}
		for (std::string str : buffer)
		{
			VehiclePack pack;
			pack.name = str.c_str();
			pack.hash = rage::joaat(pack.name);
			pack.labelText = UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(pack.hash));
			vehClass.vehicles.push_back(pack);
		}
		classes.push_back(vehClass);
		buffer.clear();
	}

	{
		VehicleClass vehClass;
		vehClass.className = "Diamond Casino";
		for (const char* str : Diamond_Casino)
		{
			std::string tmp(str);
			buffer.push_back(tmp);
			std::sort(buffer.begin(), buffer.end());
		}
		for (std::string str : buffer)
		{
			VehiclePack pack;
			pack.name = str.c_str();
			pack.hash = rage::joaat(pack.name);
			pack.labelText = UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(pack.hash));
			vehClass.vehicles.push_back(pack);
		}
		classes.push_back(vehClass);
		buffer.clear();
	}

	{
		VehicleClass vehClass;
		vehClass.className = "Diamond Casino Heist";
		for (const char* str : Diamond_Casino_Heist)
		{
			std::string tmp(str);
			buffer.push_back(tmp);
			std::sort(buffer.begin(), buffer.end());
		}
		for (std::string str : buffer)
		{
			VehiclePack pack;
			pack.name = str.c_str();
			pack.hash = rage::joaat(pack.name);
			pack.labelText = UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(pack.hash));
			vehClass.vehicles.push_back(pack);
		}
		classes.push_back(vehClass);
		buffer.clear();
	}
}

void Vehicles::refreshVehicle(VehicleData* vehData, Vehicle veh)
{
	if (ENTITY::DOES_ENTITY_EXIST(veh))
	{
		features::RequestControlOfEnt(veh);

		vehData->handle = veh;
		vehData->model = ENTITY::GET_ENTITY_MODEL(veh);
		vehData->displayName = UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(vehData->model));
		vehData->isBike = VEHICLE::IS_THIS_MODEL_A_BIKE(vehData->model);

		if (!writeData)
		{
			static bool timer_reset = true;
			static std::chrono::system_clock::time_point timer_Start;

			if (timer_reset)
			{
				timer_Start = std::chrono::system_clock::now();
				timer_reset = false;
			}

			std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - timer_Start;
			if (elapsed_seconds.count() >= 0.05)
			{
				if (VEHICLE::GET_VEHICLE_MOD_KIT(veh) != 0)
					VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

				for (int i = 0; i < 49; i++)
				{
					if (i > 16 && i < 23)
						continue;

					if (i == 47)
						continue;

					vehData->mods[i].name = getModCategoryName(i);
					vehData->mods[i].category = i;
					vehData->mods[i].options = VEHICLE::GET_NUM_VEHICLE_MODS(veh, i);
					vehData->mods[i].index = VEHICLE::GET_VEHICLE_MOD(veh, i);
					vehData->mods[i].itemName = getNormalItemTitle(veh, i, vehData->mods[i].index);

					if (vehData->lastSelectedCategory == i)
					{
						static int lastCategory = -1;
						if ((lastCategory != vehData->lastSelectedCategory) || vehData->lastSelectedModNames.empty())
						{
							lastCategory = vehData->lastSelectedCategory;
							vehData->lastSelectedModNames.clear();
							int maxcount = (vehData->mods[i].options - 1);
							for (int j = -1; j <= maxcount; j++)
							{
								vehData->lastSelectedModNames.push_back(getNormalItemTitle(veh, i, j));
							}
							vehData->isRefreshed = true;
						}
					}
				}


				vehData->other.plateTextIndex = VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(veh);
				vehData->other.plateText = VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT(veh);
				vehData->other.wheeltype = VEHICLE::GET_VEHICLE_WHEEL_TYPE(veh);
				vehData->other.isCustomTyre = vehData->mods[23].index != 0; // vehData->other.wheeltype != -1;

				vehData->togglemods.turbo = VEHICLE::IS_TOGGLE_MOD_ON(veh, 18); // turbo
				vehData->togglemods.tyreSmoke = VEHICLE::IS_TOGGLE_MOD_ON(veh, 20); // tyre smoke 
				vehData->togglemods.xenonHeadLights = VEHICLE::IS_TOGGLE_MOD_ON(veh, 22); // xenon lights
				for (int i = 0; i < 4; i++)
					vehData->togglemods.neonLights[i] = VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(veh, i); // left // right // front // back


				VEHICLE::GET_VEHICLE_COLOURS(veh, &vehData->colours.primary, &vehData->colours.secondary);
				//VEHICLE::GET_VEHICLE_MOD_COLOR_1(veh, &vehData->colours.primaryPaintType, &vehData->colours.primary, &vehData->colours.pearlescent);
				//VEHICLE::GET_VEHICLE_MOD_COLOR_2(veh, &vehData->colours.secondaryPaintType, &vehData->colours.secondary);			
				vehData->colours.isPrimaryCustom = VEHICLE::GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM(veh);
				vehData->colours.isSecondaryCustom = VEHICLE::GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(veh);
				VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, &vehData->colours.customPrimary.R, &vehData->colours.customPrimary.G, &vehData->colours.customPrimary.B);
				VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, &vehData->colours.customSecondary.R, &vehData->colours.customSecondary.G, &vehData->colours.customSecondary.B);

				vehData->colours.headlights = VEHICLE::_GET_VEHICLE_HEADLIGHTS_COLOUR(veh);
				vehData->colours.windowTint = VEHICLE::GET_VEHICLE_WINDOW_TINT(veh);
				VEHICLE::GET_VEHICLE_EXTRA_COLOURS(veh, &vehData->colours.pearlescent, &vehData->colours.wheels);
				VEHICLE::GET_VEHICLE_TYRE_SMOKE_COLOR(veh, &vehData->colours.tyreSmoke.R, &vehData->colours.tyreSmoke.G, &vehData->colours.tyreSmoke.B);
				VEHICLE::_GET_VEHICLE_NEON_LIGHTS_COLOUR(veh, &vehData->colours.neonLights.R, &vehData->colours.neonLights.G, &vehData->colours.neonLights.B);

				bool found = false;
				for (tPaintTypes paint : ePaintTypes)
				{
					for (PaintColour col : paint.colors)
					{
						if (vehData->colours.isPrimaryCustom)
							vehData->colours.primaryName = "Custom";
						else if (vehData->colours.primary == col.mainValue)
							vehData->colours.primaryName = col.name;

						if (vehData->colours.isSecondaryCustom)
							vehData->colours.secondaryName = "Custom";
						else if (vehData->colours.secondary == col.mainValue)
							vehData->colours.secondaryName = col.name;

						if (paint.paintType == 2)
							if (vehData->colours.pearlescent == col.pearlAddition)
							{
								found = true;
								vehData->colours.pearlescentName = col.name;
							}
					}
				}

				if (!found)
				{
					vehData->colours.pearlescentName = std::to_string(vehData->colours.pearlescent);
				}

				for (PaintColour col : PAINTS_Headlights)
				{
					if (!vehData->togglemods.xenonHeadLights)
					{
						vehData->colours.headlightsName = "Not Enabled";
						break;
					}

					if (vehData->colours.headlights == col.mainValue)
					{
						vehData->colours.headlightsName = col.name;
						break;
					}
				}

				found = false;
				for (PaintColour col : PAINTS_WHEELS)
				{
					if (!vehData->other.isCustomTyre) //if (vehData->colours.headlights == 255)
					{
						found = true;
						vehData->colours.headlightsName = "Not Enabled";
						break;
					}


					if (vehData->colours.wheels == col.mainValue)
					{
						found = true;
						vehData->colours.wheelName = col.name;
						break;
					}
				}

				if (!found)
				{
					vehData->colours.wheelName = std::to_string(vehData->colours.wheels);
				}

				found = false;
				for (PaintColour col : PAINTS_WindowTints)
				{
					if (vehData->colours.windowTint == col.mainValue || vehData->colours.windowTint == col.pearlAddition)
					{
						found = true;
						vehData->colours.windowTintName = col.name;
						break;
					}
				}

				if (!found)
				{
					vehData->colours.windowTintName = std::to_string(vehData->colours.windowTint);
				}

				found = false;
				for (tWheelTypes type : eWheelTypes)
				{
					if (vehData->other.wheeltype == type.wheelType)
					{
						found = true;
						vehData->other.wheelTypeName = type.displayName;
						break;
					}
				}

				if (!found)
				{
					vehData->other.wheelTypeName = std::to_string(vehData->other.wheeltype);
				}

				found = false;
				int i = 0;
				for (std::string str : PLATE_NAMES)
				{
					if (vehData->other.plateTextIndex == i)
					{
						found = true;
						vehData->other.plateTextIndexName = str;
						break;
					}
					i++;
				}

				if (!found)
				{
					vehData->other.plateTextIndexName = std::to_string(vehData->other.plateTextIndex);
				}

				timer_reset = true;
			}
		}
		else
		{
			if (VEHICLE::GET_VEHICLE_MOD_KIT(veh) != 0)
				VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

			for (int i = 0; i < 49; i++)
				VEHICLE::SET_VEHICLE_MOD(veh, i, vehData->mods[i].index, vehData->other.isCustomTyre);


			VEHICLE::TOGGLE_VEHICLE_MOD(veh, 18, vehData->togglemods.turbo); // turbo
			VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, vehData->togglemods.tyreSmoke); // tyre smoke 
			VEHICLE::TOGGLE_VEHICLE_MOD(veh, 22, vehData->togglemods.xenonHeadLights); // xenon lights
			for (int i = 0; i < 4; i++)
				VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, i, vehData->togglemods.neonLights[i]); // left // right // front // back



			VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(veh, vehData->other.plateTextIndex);
			VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh, vehData->other.plateText.c_str());
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(veh, vehData->other.wheeltype);

			VEHICLE::SET_VEHICLE_MOD_COLOR_1(veh, 0, 0, 0);
			VEHICLE::SET_VEHICLE_MOD_COLOR_2(veh, 0, 0);
			VEHICLE::SET_VEHICLE_COLOURS(veh, vehData->colours.primary, vehData->colours.secondary);

			if (vehData->colours.isPrimaryCustom)
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, vehData->colours.customPrimary.R, vehData->colours.customPrimary.G, vehData->colours.customPrimary.B);
			else
				VEHICLE::CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh);
			if (vehData->colours.isSecondaryCustom)
				VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, vehData->colours.customSecondary.R, vehData->colours.customSecondary.G, vehData->colours.customSecondary.B);
			else
				VEHICLE::CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh);

			VEHICLE::_SET_VEHICLE_HEADLIGHTS_COLOUR(veh, vehData->colours.headlights);
			VEHICLE::SET_VEHICLE_WINDOW_TINT(veh, vehData->colours.windowTint);
			VEHICLE::SET_VEHICLE_EXTRA_COLOURS(veh, vehData->colours.pearlescent, vehData->colours.wheels);
			VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, vehData->colours.tyreSmoke.R, vehData->colours.tyreSmoke.G, vehData->colours.tyreSmoke.B);
			VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, vehData->colours.neonLights.R, vehData->colours.neonLights.G, vehData->colours.neonLights.B);

			writeData = false;
		}

	}
}

/*		//ATTACH_ENTITY_TO_ENTITY ATTACH_ENTITY_TO_ENTITY_PHYSICALLY _GET_OBJECT_OFFSET_FROM_COORDS
	// PROCESS_ENTITY_ATTACHMENTS
	// GET_ZONE_AT_COORDS SET_ZONE_ENABLED // GET_ENTITY_FORWARD_VECTOR*/

void Vehicles::allocateAttachments(Attachments* attachments, Entity to)
{
	CReplayInterface* replayIntf = *g_pointers->m_replayIntf;
	CObjectInterface* objIF = replayIntf->pCObjectInterface;
	CVehicleInterface* vehIF = replayIntf->pCVehicleInterface;

	int	numObj = objIF->iMaxObjects;
	for (int i = 0; i < numObj; ++i)
	{
		CObject* pObj = objIF->get_object(i);
		if (pObj == nullptr)
			continue;
		Object obj = g_pointers->m_ptr_to_handle(pObj);


		if (ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(obj, to))
		{
			features::RequestControlOfEnt(obj);
			ObjectAttachInfo attachment;
			attachment.model = ENTITY::GET_ENTITY_MODEL(obj);
			Vector3 origin = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(to, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(to, VBone::vNames[VBone::chassis_dummy].c_str()));
			printf("orgin: %.2f, %.2f /%.2f\n", origin.x, origin.y, origin.z);

			Vector3 offset = ENTITY::GET_ENTITY_COORDS(obj, TRUE);
			printf("offset: %.2f, %.2f /%.2f\n", offset.x, offset.y, offset.z);
			attachment.X = offset.x - origin.x;
			attachment.Y = offset.y - origin.y;
			attachment.Z = offset.z - origin.z;
				
			Vector3 rot = ENTITY::GET_ENTITY_ROTATION(obj, 0);
			attachment.Pitch = ENTITY::GET_ENTITY_PITCH(obj);
			attachment.Roll = ENTITY::GET_ENTITY_ROLL(obj);
			attachment.invis = !ENTITY::IS_ENTITY_VISIBLE(to);
			attachment.Yaw = rot.y;
			attachment.dynamic = TRUE;
			attachment.collisionEnabled = !ENTITY::_GET_ENTITY_COLLISON_DISABLED(obj);
			attachment.destroyVar = false;
			
			attachments->objectsAttached.push_back(attachment);
		}
	}


	int	numeh = vehIF->iMaxVehicles;
	for (int i = 0; i < numeh; ++i)
	{
		CVehicle* pVeh = vehIF->get_vehicle(i);
		if (pVeh == nullptr)
			continue;
		Vehicle veh = g_pointers->m_ptr_to_handle(pVeh);

		if (ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(veh, to))
		{
			features::RequestControlOfEnt(veh);
			VehicleAttachInfo attachment;
			attachment.model = ENTITY::GET_ENTITY_MODEL(veh);
			VEHICLE::GET_VEHICLE_COLOURS(veh, &attachment.primCol, &attachment.secCol);
			attachment.boneIndex = VBone::chassis_dummy;
			Vector3 origin = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(to, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(to, VBone::vNames[VBone::chassis_dummy].c_str()));
			Vector3 offset = ENTITY::GET_ENTITY_COORDS(veh, TRUE);
			attachment.X = offset.x - origin.x;
			attachment.Y = offset.y - origin.y;
			attachment.Z = offset.z - origin.z;

			Vector3 rot = ENTITY::GET_ENTITY_ROTATION(veh, 0);
			attachment.Pitch = ENTITY::GET_ENTITY_PITCH(veh);
			attachment.Roll = ENTITY::GET_ENTITY_ROLL(veh);
			attachment.invis = !ENTITY::IS_ENTITY_VISIBLE(to);
			attachment.Yaw = rot.y;
			attachment.dynamic = TRUE;
			attachment.collisionEnabled = !ENTITY::_GET_ENTITY_COLLISON_DISABLED(veh);

			attachments->vehiclesAttached.push_back(attachment);
		}
	}

}

Vehicle Vehicles::spawnCustomVehicle(VehicleData data)
{
	Hash model = data.model;

	if (STREAMING::IS_MODEL_VALID(model))
	{
		STREAMING::REQUEST_MODEL(model);
		while (!STREAMING::HAS_MODEL_LOADED(model)) script::get_current()->yield();
		Vector3 ourCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
		float forward = 5.f;
		float heading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
		float xVector = forward * sin(features::degToRad(heading)) * -1.f;
		float yVector = forward * cos(features::degToRad(heading));

		if (features::bSpawnInVehicle)
			if (VEHICLE::IS_THIS_MODEL_A_HELI(model) || VEHICLE::IS_THIS_MODEL_A_PLANE(model))
				ourCoords.z += 50.f;

		Vehicle veh = VEHICLE::CREATE_VEHICLE(model, ourCoords.x + xVector, ourCoords.y + yVector, ourCoords.z, heading, true, true);

		if (*g_pointers->m_is_session_started)
		{
			DECORATOR::DECOR_SET_INT(veh, "MPBitset", 0);
		}

		features::RequestControlOfEnt(veh);

		if (features::bSpawnWithEngineOn)
			VEHICLE::SET_VEHICLE_ENGINE_ON(veh, true, true, true);

		if (features::bSpawnInVehicle)
		{
			if (VEHICLE::IS_THIS_MODEL_A_HELI(model) || VEHICLE::IS_THIS_MODEL_A_PLANE(model))
				VEHICLE::SET_HELI_BLADES_FULL_SPEED(veh);

			if (VEHICLE::IS_THIS_MODEL_A_PLANE(model))
			{
				VEHICLE::_SET_VEHICLE_JET_ENGINE_ON(veh, true);
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, 40);
			}
			PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
		}
		else
			VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);

		if (features::bSpawnWithCarGodMode)
		{
			ENTITY::SET_ENTITY_INVINCIBLE(veh, true);
			ENTITY::SET_ENTITY_PROOFS(veh, true, true, true, true, true, true, true, true);
			VEHICLE::SET_DISABLE_VEHICLE_PETROL_TANK_DAMAGE(veh, true);
			VEHICLE::SET_DISABLE_VEHICLE_PETROL_TANK_FIRES(veh, true);
			VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(veh, false);
			VEHICLE::SET_VEHICLE_CAN_BREAK(veh, false);
			VEHICLE::SET_VEHICLE_ENGINE_CAN_DEGRADE(veh, false);
			VEHICLE::SET_VEHICLE_EXPLODES_ON_HIGH_EXPLOSION_DAMAGE(veh, false);
			VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, false);
			VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(veh, false);
		}

		if (features::bSpawnCleanVehicle)
			VEHICLE::SET_VEHICLE_DIRT_LEVEL(veh, 0.f);

		if (features::bSpawnWithEffect)
		{
			STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
			GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcbarry2");
			GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_ENTITY("scr_clown_appears", veh, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, false, false, false);
		}

		{
			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

			for (int i = 0; i < 49; i++)
				VEHICLE::SET_VEHICLE_MOD(veh, i, data.mods[i].index, data.other.isCustomTyre);


			VEHICLE::TOGGLE_VEHICLE_MOD(veh, 18, data.togglemods.turbo); // turbo
			VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20, data.togglemods.tyreSmoke); // tyre smoke 
			VEHICLE::TOGGLE_VEHICLE_MOD(veh, 22, data.togglemods.xenonHeadLights); // xenon lights
			for (int i = 0; i < 4; i++)
				VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(veh, i, data.togglemods.neonLights[i]); // left // right // front // back



			VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(veh, data.other.plateTextIndex);
			VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(veh, data.other.plateText.c_str());
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(veh, data.other.wheeltype);

			VEHICLE::SET_VEHICLE_MOD_COLOR_1(veh, 0, 0, 0);
			VEHICLE::SET_VEHICLE_MOD_COLOR_2(veh, 0, 0);
			VEHICLE::SET_VEHICLE_COLOURS(veh, data.colours.primary, data.colours.secondary);

			if (data.colours.isPrimaryCustom)
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, data.colours.customPrimary.R, data.colours.customPrimary.G, data.colours.customPrimary.B);
			else
				VEHICLE::CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh);
			if (data.colours.isSecondaryCustom)
				VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, data.colours.customSecondary.R, data.colours.customSecondary.G, data.colours.customSecondary.B);
			else
				VEHICLE::CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh);

			VEHICLE::_SET_VEHICLE_HEADLIGHTS_COLOUR(veh, data.colours.headlights);
			VEHICLE::SET_VEHICLE_WINDOW_TINT(veh, data.colours.windowTint);
			VEHICLE::SET_VEHICLE_EXTRA_COLOURS(veh, data.colours.pearlescent, data.colours.wheels);
			VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, data.colours.tyreSmoke.R, data.colours.tyreSmoke.G, data.colours.tyreSmoke.B);
			VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(veh, data.colours.neonLights.R, data.colours.neonLights.G, data.colours.neonLights.B);
		}

		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
		return veh;
	}
	return NULL;
}

using namespace features;

void FunnyVehicles::GoKart()
{
	Vehicle tempVehicle = spawnVehicle(rage::joaat("Adder")); 
	for (int i = -1; i < 4; i++)
		VEHICLE::SET_VEHICLE_DOOR_BROKEN(tempVehicle, i, TRUE);
	
	// prop_yoga_mat_02
	Hash tempHash = 2057317573;
	FLOAT X = -0.2f; // 23
	FLOAT Y = 0.3f; // 465
	FLOAT Z = -0.45f; // 466
	FLOAT Pitch = 0.0f; // 467
	FLOAT Roll = 0.0f; // 476
	FLOAT Yaw = 90.0f; // 481
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	tempHash = 2057317573;
	X = -0.6000;
	Y = 0.3000;
	Z = -0.4500;
	Pitch = 0.0000;
	Roll = 0.0000;
	Yaw = 90.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	tempHash = 2057317573;
	X = -0.6000;
	Y = 0.2000;
	Z = -0.4500;
	Pitch = 0.0000;
	Roll = 0.0000;
	Yaw = 90.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	tempHash = 2057317573;
	X = -0.2000;
	Y = 0.2000;
	Z = -0.4500;
	Pitch = 0.0000;
	Roll = 0.0000;
	Yaw = 90.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);

	// prop_bumper_02
	tempHash = 2574278700;
	X = 0.1800;
	Y = 0.2500;
	Z = -0.4100;
	Pitch = 0.0000;
	Roll = 0.0000;
	Yaw = 90.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	tempHash = 2574278700;
	X = -0.9800;
	Y = 0.2500;
	Z = -0.4100;
	Pitch = 0.0000;
	Roll = 0.0000;
	Yaw = -90.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);

	// prop_weight_15k
	tempHash = 933757793;
	X = 0.2400;
	Y = -0.4400;
	Z = -0.4500;
	Pitch = 0.0000;
	Roll = 0.0000;
	Yaw = 90.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	tempHash = 933757793;
	X = 0.2700;
	Y = -0.4400;
	Z = -0.4500;
	Pitch = 0.0000;
	Roll = 0.0000;
	Yaw = 90.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	tempHash = 933757793;
	X = 0.3000;
	Y = -0.4400;
	Z = -0.4500;
	Pitch = 0.0000;
	Roll = 0.0000;
	Yaw = 90.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	tempHash = 933757793;
	X = 0.3000;
	Y = -0.4400;
	Z = -0.4500;
	Pitch = 0.0000;
	Roll = 0.0000;
	Yaw = 90.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	tempHash = 933757793;
	X = 0.3300;
	Y = -0.4400;
	Z = -0.4500;
	Pitch = 0.0000;
	Roll = 0.0000;
	Yaw = 90.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	tempHash = 933757793;
	X = 0.3600;
	Y = -0.4400;
	Z = -0.4500;
	Pitch = 0.0000;
	Roll = 0.0000;
	Yaw = 90.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	tempHash = 933757793;
	X = 0.2400;
	Y = 0.9300;
	Z = -0.4500;
	Pitch = 0.0000;
	Roll = 0.0000;
	Yaw = 90.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	tempHash = 933757793;
	X = 0.2700;
	Y = 0.9300;
	Z = -0.4500;
	Pitch = 0.0000;
	Roll = 0.0000;
	Yaw = 90.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	tempHash = 933757793;
	X = 0.3000;
	Y = 0.9300;
	Z = -0.4500;
	Pitch = 0.0000;
	Roll = 0.0000;
	Yaw = 90.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	tempHash = 933757793;
	X = 0.3300;
	Y = 0.9300;
	Z = -0.4500;
	Pitch = 0.0000;
	Roll = 0.0000;
	Yaw = 90.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	tempHash = 933757793;
	X = 0.3600;
	Y = 0.9300;
	Z = -0.4500;
	Pitch = 0.0000;
	Roll = 0.0000;
	Yaw = 90.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	tempHash = 933757793;
	X = -1.0200;
	Y = 0.9300;
	Z = -0.4500;
	Pitch = 0.0000;
	Roll = 0.0000;
	Yaw = 90.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	tempHash = 933757793;
	X = -1.0500;
	Y = 0.9300;
	Z = -0.4500;
	Pitch = 0.0000;
	Roll = 0.0000;
	Yaw = 90.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	tempHash = 933757793;
	X = -1.0800;
	Y = 0.9300;
	Z = -0.4500;
	Pitch = 0.0000;
	Roll = 0.0000;
	Yaw = 90.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	tempHash = 933757793;
	X = -1.1100;
	Y = 0.9300;
	Z = -0.4500;
	Pitch = 0.0000;
	Roll = 0.0000;
	Yaw = 90.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	tempHash = 933757793;
	X = -1.1400;
	Y = 0.9300;
	Z = -0.4500;
	Pitch = 0.0000;
	Roll = 0.0000;
	Yaw = 90.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	tempHash = 933757793;
	X = -1.0200;
	Y = -0.4400;
	Z = -0.4500;
	Pitch = 0.0000;
	Roll = 0.0000;
	Yaw = 90.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	tempHash = 933757793;
	X = -1.0500;
	Y = -0.4400;
	Z = -0.4500;
	Pitch = 0.0000;
	Roll = 0.0000;
	Yaw = 90.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	tempHash = 933757793;
	X = -1.0800;
	Y = -0.4400;
	Z = -0.4500;
	Pitch = 0.0000;
	Roll = 0.0000;
	Yaw = 90.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	tempHash = 933757793;
	X = -1.1100;
	Y = -0.4400;
	Z = -0.4500;
	Pitch = 0.0000;
	Roll = 0.0000;
	Yaw = 90.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	tempHash = 933757793;
	X = -1.1400;
	Y = -0.4400;
	Z = -0.4500;
	Pitch = 0.0000;
	Roll = 0.0000;
	Yaw = 90.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);

	// prop_weight_15k
	tempHash = 933757793;
	X = -0.4000;
	Y = 0.3800;
	Z = 0.2000;
	Pitch = -30.000;
	Roll = 0.0000;
	Yaw = 0.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);

	// prop_cs_bar
	tempHash = 3062227748;
	X = -0.4000;
	Y = 0.5900;
	Z = -0.1400;
	Pitch = 30.000;
	Roll = 0.0000;
	Yaw = 0.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);

	// prop_car_seat
	tempHash = 1382419899;
	X = -0.4000;
	Y = -0.1500;
	Z = -0.5000;
	Pitch = 0.0000;
	Roll = 0.0000;
	Yaw = 180.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);

	// prop_power_cell
	tempHash = 2235081574;
	X = -0.1500;
	Y = 1.0700;
	Z = -0.4500;
	Pitch = 0.0000;
	Roll = 0.0000;
	Yaw = 90.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	tempHash = 2235081574;
	X = -0.6500;
	Y = 1.0700;
	Z = -0.4500;
	Pitch = 0.0000;
	Roll = 0.0000;
	Yaw = 90.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	tempHash = 2235081574;
	X = -0.4000;
	Y = 1.0700;
	Z = -0.4500;
	Pitch = 0.0000;
	Roll = 0.0000;
	Yaw = 90.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	tempHash = 2235081574;
	X = -0.1500;
	Y = -0.5700;
	Z = -0.4500;
	Pitch = 0.0000;
	Roll = 0.0000;
	Yaw = 90.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	tempHash = 2235081574;
	X = -0.6500;
	Y = -0.5700;
	Z = -0.4500;
	Pitch = 0.0000;
	Roll = 0.0000;
	Yaw = 90.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	tempHash = 2235081574;
	X = -0.4000;
	Y = -0.5700;
	Z = -0.4500;
	Pitch = 0.0000;
	Roll = 0.0000;
	Yaw = 90.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);

	printf("spawned GoKart\n");
}

void FunnyVehicles::DragsterBike()
{
	Vehicle tempVehicle = spawnVehicle(rage::joaat("Akuma")); 

														 // prop_cartwheel_01
	Hash tempHash = 4137416026;
	FLOAT X = -0.07f; // 23
	FLOAT Y = 1.1f; // 465
	FLOAT Z = 0.03f; // 466
	FLOAT Pitch = 0.0f; // 467
	FLOAT Roll = 90.0f; // 476
	FLOAT Yaw = 0.0f; // 481
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);

	// prop_cs_bar
	tempHash = 3062227748;
	X = -0.1500;
	Y = 0.7800;
	Z = 0.2100;
	Pitch = 60.0000;
	Roll = 0.0000;
	Yaw = 0.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	tempHash = 3062227748;
	X = 0.1500;
	Y = 0.7800;
	Z = 0.2100;
	Pitch = 60.0000;
	Roll = 0.0000;
	Yaw = 0.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	tempHash = 3062227748;
	X = 0.1500;
	Y = 0.2800;
	Z = 0.0800;
	Pitch = -30.0000;
	Roll = 0.0000;
	Yaw = 0.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	tempHash = 3062227748;
	X = -0.1500;
	Y = 0.2800;
	Z = 0.0800;
	Pitch = -30.0000;
	Roll = 0.0000;
	Yaw = 0.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	tempHash = 3062227748;
	X = -0.1500;
	Y = -0.2900;
	Z = -0.2400;
	Pitch = -93.0000;
	Roll = 0.0000;
	Yaw = 0.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	tempHash = 3062227748;
	X = 0.1500;
	Y = -0.2900;
	Z = -0.2400;
	Pitch = -93.0000;
	Roll = 0.0000;
	Yaw = 0.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	tempHash = 3062227748;
	X = 0.1500;
	Y = -0.3400;
	Z = -0.0200;
	Pitch = -59.0000;
	Roll = 0.0000;
	Yaw = 0.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	tempHash = 3062227748;
	X = -0.1500;
	Y = -0.3400;
	Z = -0.0200;
	Pitch = -59.0000;
	Roll = 0.0000;
	Yaw = 0.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	tempHash = 3062227748;
	X = -0.1500;
	Y = 0.1400;
	Z = 0.2600;
	Pitch = -59.0000;
	Roll = 0.0000;
	Yaw = 0.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	tempHash = 3062227748;
	X = 0.1500;
	Y = 0.1400;
	Z = 0.2600;
	Pitch = -59.0000;
	Roll = 0.0000;
	Yaw = 0.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);

	// prop_cs_bar
	tempHash = 3062227748;
	X = 0.0000;
	Y = 0.4600;
	Z = 0.4000;
	Pitch = 0.0000;
	Roll = 90.0000;
	Yaw = 0.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);

	// prop_wheel_06
	tempHash = 3730985457;
	X = 0.0000;
	Y = -0.6600;
	Z = -0.2100;
	Pitch = 0.0000;
	Roll = 0.0000;
	Yaw = 90.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);

	// prop_power_cell
	tempHash = 2235081574;
	X = 0.0000;
	Y = -0.3900;
	Z = 0.1600;
	Pitch = -40.0000;
	Roll = 0.0000;
	Yaw = 0.0000;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1);

	ENTITY::SET_ENTITY_VISIBLE(tempVehicle, true, 0);
	ENTITY::SET_ENTITY_ALPHA(tempVehicle, 0, 0);
	//SET_VEHICLE_AS_NO_LONGER_NEEDED(&tempVehicle);

	printf("spawned Dragstar\n");

}

void FunnyVehicles::WeedWheelsBike()
{
	Vehicle tempVehicle = spawnVehicle(rage::joaat("BATI")); 

	auto wheel_rf = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(tempVehicle, VBone::vNames[VBone::wheel_rf].c_str());
	auto wheel_lf = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(tempVehicle, VBone::vNames[VBone::wheel_lf].c_str());
	auto handlebar = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(tempVehicle, VBone::vNames[VBone::handlebars].c_str());

	// prop_rub_wheel_02
	Hash tempHash = 3437004565;
	FLOAT X = 0.0f;
	FLOAT Y = 0.0f;
	FLOAT Z = 0.0f;
	FLOAT Pitch = 0.0f;
	FLOAT Roll = 0.0f;
	FLOAT Yaw = 0.0f;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1, wheel_rf);
	tempHash = 3437004565;
	X = 0.0f;
	Y = 0.0f;
	Z = 0.0f;
	Pitch = 0.0f;
	Roll = 0.0f;
	Yaw = 0.0f;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1, wheel_lf);

	// prop_byard_pipe_01
	tempHash = 2971578861;
	X = 0.0f;
	Y = 0.0f;
	Z = 0.0f;
	Pitch = 0.0f;
	Roll = 0.0f;
	Yaw = 0.0f;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1, wheel_lf);
	tempHash = 2971578861;
	X = 0.0f;
	Y = 0.0f;
	Z = 0.0f;
	Pitch = 0.0f;
	Roll = 0.0f;
	Yaw = 0.0f;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1, wheel_lf);

	// prop_rub_wheel_01
	tempHash = 103020963;
	X = 2.1f;
	Y = 0.0f;
	Z = 0.0f;
	Pitch = 0.0f;
	Roll = 0.0f;
	Yaw = 0.0f;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1, wheel_lf);
	tempHash = 103020963;
	X = -2.0f;
	Y = 0.0f;
	Z = 0.0f;
	Pitch = 0.0f;
	Roll = 0.0f;
	Yaw = 0.0f;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1, wheel_lf);

	// prop_minigun_01
	tempHash = 3365286072;
	X = 1.0f;
	Y = 0.0f;
	Z = 0.5f;
	Pitch = 0.0f;
	Roll = 0.0f;
	Yaw = 90.0f;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1, -1);
	tempHash = 3365286072;
	X = -1.0f;
	Y = 0.0f;
	Z = 0.5f;
	Pitch = 0.0f;
	Roll = 0.0f;
	Yaw = 90.0f;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1, -1);

	// prop_weed_01
	tempHash = 452618762;
	X = 2.1f;
	Y = 0.0f;
	Z = -1.0f;
	Pitch = 0.0f;
	Roll = 0.0f;
	Yaw = 0.0f;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1, wheel_lf);
	tempHash = 452618762;
	X = -2.0f;
	Y = 0.0f;
	Z = -1.0f;
	Pitch = 0.0f;
	Roll = 0.0f;
	Yaw = 0.0f;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1, wheel_lf);

	// prop_car_seat
	tempHash = 1382419899;
	X = 0.0f;
	Y = -0.4f;
	Z = 0.4f;
	Pitch = 22.0f;
	Roll = 0.0f;
	Yaw = 180.0f;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1, -1);

	// prop_cs_dildo_01
	tempHash = 3872089630;
	X = 0.29f;
	Y = -0.09f;
	Z = -0.36f;
	Pitch = 33.31f;
	Roll = 279.39f;
	Yaw = -34.43f;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1, handlebar);
	tempHash = 3872089630;
	X = 0.3f;
	Y = -0.08f;
	Z = -0.37f;
	Pitch = 111.699f;
	Roll = 0.0f;
	Yaw = -8.3f;
	att_obj_to_veh(tempHash, tempVehicle, X, Y, Z, Pitch, Roll, Yaw, 1, handlebar);

	ENTITY::SET_ENTITY_VISIBLE(tempVehicle, true, 0);
	ENTITY::SET_ENTITY_ALPHA(tempVehicle, 0, 0);
	//tempVehicle.NoLongerNeeded();

	printf("spawned WeedBike\n");
}

void FunnyVehicles::YachtAirship()
{
	Vehicle vehicle = spawnVehicle(rage::joaat("BLIMP")); // Blimp

	auto bone_bodyshell = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, VBone::vNames[VBone::bodyshell].c_str());

	Hash hash;

	hash = 0x4FCAD2E0; // apa_mp_apa_yacht
	att_obj_to_veh(hash, vehicle, 0, 0, 0, 0, 0, 90.0f, true, bone_bodyshell, false, true);

	hash = 0xBCDAC9E7; // apa_mp_apa_yacht_win
	att_obj_to_veh(hash, vehicle, 0, 0, 0, 0, 0, 90.0f, true, bone_bodyshell, false, true);

	hash = 0xB4AA481D; // apa_mp_apa_yacht_option2
	att_obj_to_veh(hash, vehicle, 0, 0, 14.57f, 0, 0, 90.0f, true, bone_bodyshell, false, true);

	hash = 0x75F724B2; // apa_mp_apa_yacht_o2_rail_a
	att_obj_to_veh(hash, vehicle, 0, 0, 14.57f, 0, 0, 90.0f, true, bone_bodyshell, false, true);

	hash = 0x98B5E3D4; // apa_mp_apa_yacht_jacuzzi_ripple1
	att_obj_to_veh(hash, vehicle, 2.00f, -51.00f, 0, 0, 0, 90.0f, true, bone_bodyshell, false, true);

	hash = 0x949F49C7; // apa_mp_apa_y1_l1a
	att_obj_to_veh(hash, vehicle, 0, 0, 14.57f, 0, 0, 90.0f, true, bone_bodyshell, false, true);

	hash = 0x2E51B0EA; // apa_mp_apa_y3_l2b
	att_obj_to_veh(hash, vehicle, 0, 0, 14.57f, 0, 0, 90.0f, true, bone_bodyshell, false, true);

	hash = 0x956974FD; // apa_mp_apa_yacht_door2
	att_obj_to_veh(hash, vehicle, 1.29f, -36.85f, 0.65f, 0, 0, 90.0f, true, bone_bodyshell, false, true);
	att_obj_to_veh(hash, vehicle, 3.40f, 0, 6.70, 0, 0, -180.0f, true, bone_bodyshell, false, true);
	att_obj_to_veh(hash, vehicle, 0.60f, 0, 6.70f, 0, 0, 0, true, bone_bodyshell, false, true);

	printf("spawned YachtAirship\n");
}

void FunnyVehicles::YachtAirshipWithFans()
{
	Vehicle vehicle = spawnVehicle(rage::joaat("BLIMP")); // Blimp

	auto bone_bodyshell =  ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, VBone::vNames[VBone::bodyshell].c_str());

	Hash hash;

	hash = 0x4FCAD2E0; // apa_mp_apa_yacht
	att_obj_to_veh(hash, vehicle, 0, 0, 0, 0, 0, 90.0f, true, bone_bodyshell, false, true);

	hash = 0xBCDAC9E7; // apa_mp_apa_yacht_win
	att_obj_to_veh(hash, vehicle, 0, 0, 0, 0, 0, 90.0f, true, bone_bodyshell, false, true);

	hash = 0xB4AA481D; // apa_mp_apa_yacht_option2
	att_obj_to_veh(hash, vehicle, 0, 0, 14.57f, 0, 0, 90.0f, true, bone_bodyshell, false, true);

	hash = 0x75F724B2; // apa_mp_apa_yacht_o2_rail_a
	att_obj_to_veh(hash, vehicle, 0, 0, 14.57f, 0, 0, 90.0f, true, bone_bodyshell, false, true);

	hash = 0x98B5E3D4; // apa_mp_apa_yacht_jacuzzi_ripple1
	att_obj_to_veh(hash, vehicle, 2.00f, -51.00f, 0, 0, 0, 90.0f, true, bone_bodyshell, false, true);

	hash = 0x949F49C7; // apa_mp_apa_y1_l1a
	att_obj_to_veh(hash, vehicle, 0, 0, 14.57f, 0, 0, 90.0f, true, bone_bodyshell, false, true);

	hash = 0x2E51B0EA; // apa_mp_apa_y3_l2b
	att_obj_to_veh(hash, vehicle, 0, 0, 14.57f, 0, 0, 90.0f, true, bone_bodyshell, false, true);

	hash = 0x956974FD; // apa_mp_apa_yacht_door2
	att_obj_to_veh(hash, vehicle, 1.29f, -36.85f, 0.65f, 0, 0, 90.0f, true, bone_bodyshell, false, true);
	att_obj_to_veh(hash, vehicle, 3.40f, 0, 6.70, 0, 0, -180.0f, true, bone_bodyshell, false, true);
	att_obj_to_veh(hash, vehicle, 0.60f, 0, 6.70f, 0, 0, 0, true, bone_bodyshell, false, true);

	hash = 0x745F3383; // prop_windmill_01
	att_obj_to_veh(hash, vehicle, 4.30f, 36.10f, 0.50f, -90.0, 0, 90.0f, true, bone_bodyshell, false, true);
	att_obj_to_veh(hash, vehicle, 0.70f, 36.10f, 0.50f, -90.0, 0, -90.0f, true, bone_bodyshell, false, true);
	att_obj_to_veh(hash, vehicle, 4.30f, -8.40f, -4.30f, -90.0, 0, 90.0f, true, bone_bodyshell, false, true);
	att_obj_to_veh(hash, vehicle, 0.70f, -8.40f, -4.30f, -90.0, 0, -90.0f, true, bone_bodyshell, false, true);
	att_obj_to_veh(hash, vehicle, 5.00f, -47.0f, -4.0f, 0, -110.0f, 0, true, bone_bodyshell, false, true);
	att_obj_to_veh(hash, vehicle, -2.10f, -47.0f, -4.0f, 0, 110.0f, 0, true, bone_bodyshell, false, true);

	printf("spawned YachtAirshipWithFans\n");
}

void FunnyVehicles::FibBuilding()
{
	Vehicle vehicle = spawnVehicle(rage::joaat("BLIMP")); // Blimp

	auto bone_chassis = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, VBone::vNames[VBone::chassis_dummy].c_str());

	Hash building = 0xAC4365DD; // dt1_05_build1_damage
	Vector3 buildingDimension1, buildingDimension2;
	GAMEPLAY::GET_MODEL_DIMENSIONS(building, &buildingDimension1, &buildingDimension2);
	Vector3 ModelDimension1, ModelDimension2;
	GAMEPLAY::GET_MODEL_DIMENSIONS(rage::joaat("BLIMP"), &ModelDimension1, &ModelDimension2);

	att_obj_to_veh(building, vehicle, 0, 0, ModelDimension1.z - ModelDimension2.z, 0, 0, 0, 1, bone_chassis, false, true, false); // Don't set as no longer needed

	printf("spawned FibBuilding\n");
}

void FunnyVehicles::BlackNoisyUFO()
{
	Vehicle vehicle = spawnVehicle(rage::joaat("Valkyrie"));

	auto bone_chassis = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, VBone::vNames[VBone::chassis_dummy].c_str());

	Hash hash;

	hash = rage::joaat("dt1_tc_dufo_core"); // dt1_tc_dufo_core // 0x7D79DAD4
	att_obj_to_veh(hash, vehicle, 0, 0, 0, 0, 0, 0, 1, bone_chassis, true);

	printf("spawned BlackNoisyUFO\n");
}

void FunnyVehicles::ToyCar()
{
	Vehicle vehicle = spawnVehicle(rage::joaat("T20"));
	for (int i = -1; i < 4; i++)
		VEHICLE::SET_VEHICLE_DOOR_BROKEN(vehicle, i, TRUE);

	// ind_prop_dlc_roller_car
	Hash hash = 0x5C05F6C1;
	FLOAT X = 0.0f;
	FLOAT Y = 0.2f;
	FLOAT Z = -0.5f;
	FLOAT Pitch = 0.0f;
	FLOAT Roll = 0.0f;
	FLOAT Yaw = 180.0f;
	att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);

	// prop_hd_seats_01
	hash = 0x0A5654F6;
	X = 0.0f;
	Y = 0.28f;
	Z = -0.13f;
	Pitch = 0.0f;
	Roll = 0.0f;
	Yaw = 0.0f;
	att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);

	// prop_wheel_03
	hash = 0xD2FB3B23;
	X = 0.95f;
	Y = 1.2f;
	Z = -0.2f;
	Pitch = 0.0f;
	Roll = 0.0f;
	Yaw = -90.0f;
	att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	hash = 0xD2FB3B23;
	X = 1.06f;
	Y = 1.2f;
	Z = -0.2f;
	Pitch = 0.0f;
	Roll = 0.0f;
	Yaw = -90.0f;
	att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	hash = 0xD2FB3B23;
	X = 0.98f;
	Y = -0.91f;
	Z = -0.21f;
	Pitch = 0.0f;
	Roll = 0.0f;
	Yaw = -90.0f;
	att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	hash = 0xD2FB3B23;
	X = 1.15f;
	Y = -0.91f;
	Z = -0.21f;
	Pitch = 0.0f;
	Roll = 0.0f;
	Yaw = -90.0f;
	att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	hash = 0xD2FB3B23;
	X = -0.98f;
	Y = 1.2f;
	Z = -0.21f;
	Pitch = 0.0f;
	Roll = 0.0f;
	Yaw = -90.0f;
	att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	hash = 0xD2FB3B23;
	X = -1.15f;
	Y = 1.2f;
	Z = -0.21f;
	Pitch = 0.0f;
	Roll = 0.0f;
	Yaw = -90.0f;
	att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	hash = 0xD2FB3B23;
	X = -0.98f;
	Y = -0.91f;
	Z = -0.21f;
	Pitch = 0.0f;
	Roll = 0.0f;
	Yaw = -90.0f;
	att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	hash = 0xD2FB3B23;
	X = -1.10f;
	Y = -0.91f;
	Z = -0.21f;
	Pitch = 0.0f;
	Roll = 0.0f;
	Yaw = -90.0f;
	att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);

	// prop_bumper_03
	hash = 0xB9579FFA;
	X = 0.0f;
	Y = 1.33f;
	Z = -1.8f;
	Pitch = 0.0f;
	Roll = 0.0f;
	Yaw = 180.0f;
	att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);

	// prop_compressor_03
	hash = 0xE08EF8F2;
	X = 0.03f;
	Y = 1.34f;
	Z = -0.82f;
	Pitch = 0.0f;
	Roll = 0.0f;
	Yaw = -90.0f;
	att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);

	// hei_prop_wall_alarm_off
	hash = 0x889E3E33;
	X = -0.55f;
	Y = -1.38f;
	Z = -0.38f;
	Pitch = 0.0f;
	Roll = 0.0f;
	Yaw = 180.0f;
	att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	hash = 0x889E3E33;
	X = 0.55f;
	Y = -1.38f;
	Z = -0.38f;
	Pitch = 0.0f;
	Roll = 0.0f;
	Yaw = 180.0f;
	att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);

	// prop_car_exhaust_01
	hash = 0xFC612F85;
	X = 0.26f;
	Y = -0.76f;
	Z = -0.49f;
	Pitch = 0.0f;
	Roll = 0.0f;
	Yaw = 0.0f;
	att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	hash = 0xFC612F85;
	X = 0.18f;
	Y = -0.76f;
	Z = -0.49f;
	Pitch = 0.0f;
	Roll = 0.0f;
	Yaw = 0.0f;
	att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	hash = 0xFC612F85;
	X = -0.40f;
	Y = -0.76f;
	Z = -0.49f;
	Pitch = 0.0f;
	Roll = 0.0f;
	Yaw = 0.0f;
	att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	hash = 0xFC612F85;
	X = -0.32f;
	Y = -0.76f;
	Z = -0.49f;
	Pitch = 0.0f;
	Roll = 0.0f;
	Yaw = 0.0f;
	att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);

	// prop_sh_mr_rasp_01
	hash = 0xD59D6B1A;
	X = -0.01f;
	Y = -0.82f;
	Z = 0.11f;
	Pitch = 0.0f;
	Roll = 0.0f;
	Yaw = 180.0f;
	att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);

	// prop_voltmeter_01
	hash = 0x8F4674EC;
	X = 0.0f;
	Y = 0.98f;
	Z = 0.02f;
	Pitch = 0.0f;
	Roll = 0.0f;
	Yaw = 0.0f;
	att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);

	// prop_spot_01
	hash = 0x5376930C;
	X = -0.57f;
	Y = 1.49f;
	Z = -0.04f;
	Pitch = 0.0f;
	Roll = 0.0f;
	Yaw = 180.0f;
	att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);
	hash = 0x5376930C;
	X = 0.55f;
	Y = 1.49f;
	Z = -0.04f;
	Pitch = 0.0f;
	Roll = 0.0f;
	Yaw = 180.0f;
	att_obj_to_veh(hash, vehicle, X, Y, Z, Pitch, Roll, Yaw, 1);


	printf("spawned ToyCar\n");
}
void FunnyVehicles::Adderuma()
{
	Vehicle vehicle = spawnVehicle(rage::joaat("adder"));

	auto bone_bodyshell = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, VBone::vNames[VBone::bodyshell].c_str());

	att_veh_to_veh(rage::joaat("KURUMA2"), vehicle, PAINTS_MATTE.at(0).mainValue, PAINTS_MATTE.at(0).mainValue, 0, 0, 0, 0, 0, 0, false, bone_bodyshell);

	VEHICLE::SET_VEHICLE_COLOURS(vehicle, PAINTS_MATTE.at(0).mainValue, PAINTS_MATTE.at(0).mainValue);
	printf("spawned Adderuma\n");
}
void FunnyVehicles::Zentornuma()
{
	Vehicle vehicle = spawnVehicle(rage::joaat("zentorno"));

	auto bone_bodyshell = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, VBone::vNames[VBone::bodyshell].c_str());

	att_veh_to_veh(rage::joaat("KURUMA2"), vehicle, PAINTS_MATTE.at(3).mainValue, PAINTS_MATTE.at(0).mainValue, 0, 0.2230f, -0.0280f, 0, 0, 0, false, bone_bodyshell);

	VEHICLE::SET_VEHICLE_COLOURS(vehicle, PAINTS_MATTE.at(3).mainValue, PAINTS_MATTE.at(3).mainValue);

	printf("spawned Zentornuma\n");
}
void FunnyVehicles::TurismoRuma()
{
	Vehicle vehicle = spawnVehicle(rage::joaat("TurismoR"));

	auto bone_bodyshell = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, VBone::vNames[VBone::bodyshell].c_str());

	att_veh_to_veh(rage::joaat("KURUMA2"), vehicle, PAINTS_MATTE.at(3).mainValue, PAINTS_MATTE.at(0).mainValue, 0, 0.0400f, 0.4000f, 0, 0, 0, false, bone_bodyshell);

	VEHICLE::SET_VEHICLE_COLOURS(vehicle, PAINTS_MATTE.at(3).mainValue, PAINTS_MATTE.at(3).mainValue);

	printf("spawned TurismoRuma\n");
}
void FunnyVehicles::EnturumaXF()
{
	Vehicle vehicle = spawnVehicle(rage::joaat("EntityXF"));

	auto bone_bodyshell = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, VBone::vNames[VBone::bodyshell].c_str());

	att_veh_to_veh(rage::joaat("KURUMA2"), vehicle, PAINTS_MATTE.at(0).mainValue, PAINTS_MATTE.at(0).mainValue, 0, 0.1410f, 0.1700f, 0, 0, 0, false, bone_bodyshell);

	VEHICLE::SET_VEHICLE_COLOURS(vehicle, PAINTS_MATTE.at(0).mainValue, PAINTS_MATTE.at(0).mainValue);

	printf("spawned EnturumaXF\n");
}

void FunnyVehicles::Osirisuma()
{
	Vehicle vehicle = spawnVehicle(rage::joaat("Osiris"));

	auto bone_bodyshell = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, VBone::vNames[VBone::bodyshell].c_str());

	att_veh_to_veh(rage::joaat("KURUMA2"), vehicle, VehicleColoursMatte::COLOR_MATTE_YELLOW, VehicleColoursMatte::COLOR_MATTE_YELLOW, 0, 0.1300f, 0.0400f, 0, 0, 0, false, bone_bodyshell);

	VEHICLE::SET_VEHICLE_COLOURS(vehicle, VehicleColoursMatte::COLOR_MATTE_YELLOW, VehicleColoursMatte::COLOR_MATTE_RED);

	VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);
	for (int i = 0; i < 49; i++)
	{
		if (i > 16 && i < 23)
			continue;

		VEHICLE::SET_VEHICLE_MOD(vehicle, i, VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, i) - 1, false);
	}

	printf("spawned Osirisuma\n");
}
void FunnyVehicles::T20uma()
{
	Vehicle vehicle = spawnVehicle(rage::joaat("T20"));

	auto bone_bodyshell = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, VBone::vNames[VBone::bodyshell].c_str());

	att_veh_to_veh(rage::joaat("KURUMA2"), vehicle, VehicleColoursMatte::COLOR_MATTE_YELLOW, VehicleColoursMatte::COLOR_MATTE_BLACK, 0, 0.1400f, -0.0800f, 0, 0, 0, false, bone_bodyshell);

	VEHICLE::SET_VEHICLE_COLOURS(vehicle, VehicleColoursMatte::COLOR_MATTE_YELLOW, VehicleColoursMatte::COLOR_MATTE_BLACK);

	printf("spawned T20uma\n");
}
void FunnyVehicles::Feltzeruma()
{
	Vehicle vehicle = spawnVehicle(rage::joaat("Feltzer2"));

	auto bone_bodyshell = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, VBone::vNames[VBone::bodyshell].c_str());

	att_veh_to_veh(rage::joaat("KURUMA2"), vehicle, VehicleColoursMatte::COLOR_MATTE_LIME_GREEN, VehicleColoursMatte::COLOR_MATTE_SCHAFTER_PURPLE, 0, -0.1530f, 0.0770f, 0, 0, 0, false, bone_bodyshell);

	VEHICLE::SET_VEHICLE_COLOURS(vehicle, VehicleColoursMatte::COLOR_MATTE_LIME_GREEN, VehicleColoursMatte::COLOR_MATTE_SCHAFTER_PURPLE);

	printf("spawned Feltzeruma\n");
}
void FunnyVehicles::Banshuma()
{
	Vehicle vehicle = spawnVehicle(rage::joaat("Banshee"));

	auto bone_bodyshell = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, VBone::vNames[VBone::bodyshell].c_str());

	att_veh_to_veh(rage::joaat("KURUMA2"), vehicle, VehicleColoursMatte::COLOR_MATTE_RED, VehicleColoursMatte::COLOR_MATTE_BLACK, 0, -0.0500f, 0.0500f, 4.500f, 0, 0, false, bone_bodyshell);

	VEHICLE::SET_VEHICLE_COLOURS(vehicle, VehicleColoursMatte::COLOR_MATTE_RED, VehicleColoursMatte::COLOR_MATTE_BLACK);

	printf("spawned Banshuma\n");
}
void FunnyVehicles::Nightshuma()
{
	Vehicle vehicle = spawnVehicle(rage::joaat("Nightshade"));

	auto bone_bodyshell = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, VBone::vNames[VBone::bodyshell].c_str());

	att_veh_to_veh(rage::joaat("KURUMA2"), vehicle, VehicleColoursMatte::COLOR_MATTE_YELLOW, VehicleColoursMatte::COLOR_MATTE_BLACK, 0, 0.0100f, 0.3100f, 5.1600f, 0, 0, false, bone_bodyshell);

	VEHICLE::SET_VEHICLE_COLOURS(vehicle, VehicleColoursMatte::COLOR_MATTE_YELLOW, VehicleColoursMatte::COLOR_MATTE_BLACK);

	VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);
	for (int i = 0; i < 49; i++)
	{
		if (i > 16 && i < 23)
			continue;

		VEHICLE::SET_VEHICLE_MOD(vehicle, i, VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, i) - 1, false);
	}

	printf("spawned Nightshuma\n");
}
void FunnyVehicles::Bulletuma()
{
	Vehicle vehicle = spawnVehicle(rage::joaat("Bullet"));

	auto bone_bodyshell = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, VBone::vNames[VBone::bodyshell].c_str());

	att_veh_to_veh(rage::joaat("KURUMA2"), vehicle, VehicleColoursClassic::COLOR_CLASSIC_GALAXY_BLUE, VehicleColoursMatte::COLOR_MATTE_BLACK, 0, -0.1900f, 0.2600f, 1.5200f, 0, 0, false, bone_bodyshell);

	VEHICLE::SET_VEHICLE_COLOURS(vehicle, VehicleColoursClassic::COLOR_CLASSIC_GALAXY_BLUE, VehicleColoursMatte::COLOR_MATTE_BLACK);

	VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);
	for (int i = 0; i < 49; i++)
	{
		if (i > 16 && i < 23)
			continue;

		VEHICLE::SET_VEHICLE_MOD(vehicle, i, VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, i) - 1, false);
	}

	printf("spawned Bulletuma\n");
}

void FunnyVehicles::LandJetski()
{
	Vehicle vehicle = spawnVehicle(rage::joaat("blazer"));

	auto bone_bodyshell = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, VBone::vNames[VBone::bodyshell].c_str());

	att_veh_to_veh(rage::joaat("SeaShark2"), vehicle, 112, 35, 0, -0.1800f, -0.4600f, 0, 0, 0, false, bone_bodyshell);

	VEHICLE::SET_VEHICLE_COLOURS(vehicle, 112, 35);

	printf("spawned LandJetski\n");
}
void FunnyVehicles::MonsterTruck_BoatChassis()
{
	Vehicle vehicle = spawnVehicle(rage::joaat("Marshall"));
	for (int i = -1; i < 4; i++)
		VEHICLE::SET_VEHICLE_DOOR_BROKEN(vehicle, i, TRUE);
	auto bone_bodyshell = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, VBone::vNames[VBone::bodyshell].c_str());


	att_veh_to_veh(rage::joaat("MARQUIS"), vehicle, PAINTS_MATTE.at(3).mainValue, PAINTS_MATTE.at(3).mainValue, 0, 0, 0.7580f, 0, 0, 0, false, bone_bodyshell, true);

	VEHICLE::SET_VEHICLE_COLOURS(vehicle, PAINTS_MATTE.at(3).mainValue, PAINTS_MATTE.at(3).mainValue);

	printf("spawned MonsterTruck_BoatChassis\n");
}
void FunnyVehicles::MonsterTruck_TankChassis()
{
	Vehicle vehicle = spawnVehicle(rage::joaat("Marshall"));
	for (int i = -1; i < 4; i++)
		VEHICLE::SET_VEHICLE_DOOR_BROKEN(vehicle, i, TRUE);
	auto bone_bodyshell = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, VBone::vNames[VBone::bodyshell].c_str());

	att_veh_to_veh(rage::joaat("RHINO"), vehicle, VehicleColoursMatte::COLOR_MATTE_BLACK, VehicleColoursMatte::COLOR_MATTE_BLACK, 0, 0, 1.4330f, 0, 0, 0, false, bone_bodyshell, true);

	VEHICLE::SET_VEHICLE_COLOURS(vehicle, VehicleColoursMatte::COLOR_MATTE_BLACK, VehicleColoursMatte::COLOR_MATTE_BLACK);

	printf("spawned MonsterTruck_TankChassis\n");
}
void FunnyVehicles::MonsterTruck_HelicopterChassis()
{
	Vehicle vehicle = spawnVehicle(rage::joaat("Marshall"));
	for (int i = -1; i < 4; i++)
		VEHICLE::SET_VEHICLE_DOOR_BROKEN(vehicle, i, TRUE);
	auto bone_bodyshell = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, VBone::vNames[VBone::bodyshell].c_str());

	att_veh_to_veh(rage::joaat("SAVAGE"), vehicle, VehicleColoursMatte::COLOR_MATTE_MIDNIGHT_PURPLE, VehicleColoursMatte::COLOR_MATTE_MIDNIGHT_PURPLE, 0, -0.2400f, 0.3100f, 0, 0, 0, false, bone_bodyshell, true);

	VEHICLE::SET_VEHICLE_COLOURS(vehicle, VehicleColoursMatte::COLOR_MATTE_MIDNIGHT_PURPLE, VehicleColoursMatte::COLOR_MATTE_MIDNIGHT_PURPLE);

	printf("spawned MonsterTruck_HelicopterChassis\n");
}
void FunnyVehicles::MonsterTruck_RVChassis()
{
	Vehicle vehicle = spawnVehicle(rage::joaat("Marshall"));
	for (int i = -1; i < 4; i++)
		VEHICLE::SET_VEHICLE_DOOR_BROKEN(vehicle, i, TRUE);
	auto bone_bodyshell = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, VBone::vNames[VBone::bodyshell].c_str());

	att_veh_to_veh(rage::joaat("JOURNEY"), vehicle, VehicleColoursMatte::COLOR_MATTE_MIDNIGHT_BLUE, VehicleColoursMatte::COLOR_MATTE_MIDNIGHT_BLUE, 0, 0.2000f, 0.6400f, 0, 0, 0, false, bone_bodyshell, true);

	VEHICLE::SET_VEHICLE_COLOURS(vehicle, VehicleColoursMatte::COLOR_MATTE_MIDNIGHT_BLUE, VehicleColoursMatte::COLOR_MATTE_MIDNIGHT_BLUE);

	VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);
	for (int i = 0; i < 49; i++)
	{
		if (i > 16 && i < 23)
			continue;

		VEHICLE::SET_VEHICLE_MOD(vehicle, i, VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, i) - 1, false);
	}

	printf("spawned MonsterTruck_RVChassis\n");
}
void FunnyVehicles::MonsterTruck_FighterJetChassis()
{
	Vehicle vehicle = spawnVehicle(rage::joaat("Marshall"));
	for (int i = -1; i < 4; i++)
		VEHICLE::SET_VEHICLE_DOOR_BROKEN(vehicle, i, TRUE);
	auto bone_bodyshell = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, VBone::vNames[VBone::bodyshell].c_str());

	att_veh_to_veh(rage::joaat("HYDRA"), vehicle, VehicleColoursMatte::COLOR_MATTE_BROWN, VehicleColoursMatte::COLOR_MATTE_BROWN, 0, 2.8800f, 1.2800f, 0, 0, 0, false, bone_bodyshell, true);

	VEHICLE::SET_VEHICLE_COLOURS(vehicle, VehicleColoursMatte::COLOR_MATTE_BROWN, VehicleColoursMatte::COLOR_MATTE_BROWN);

	printf("spawned MonsterTruck_FighterJetChassis\n");
}
void FunnyVehicles::MonsterTrainTruck()
{
	Vehicle vehicle = spawnVehicle(rage::joaat("Marshall"));
	for (int i = -1; i < 4; i++)
		VEHICLE::SET_VEHICLE_DOOR_BROKEN(vehicle, i, TRUE);
	auto bone_bodyshell = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, VBone::vNames[VBone::bodyshell].c_str());

	att_veh_to_veh(rage::joaat("FREIGHT"), vehicle, VehicleColoursMatte::COLOR_MATTE_DARK_BLUE, VehicleColoursMatte::COLOR_MATTE_RED, 0, 1.0600f, 0, 0, 0, 0, false, bone_bodyshell, true);

	VEHICLE::SET_VEHICLE_COLOURS(vehicle, VehicleColoursMatte::COLOR_MATTE_DARK_BLUE, VehicleColoursMatte::COLOR_MATTE_RED);

	printf("spawned MonsterTrainTruck\n");
}
void FunnyVehicles::ChinoODeath()
{
	Vehicle vehicle = spawnVehicle(rage::joaat("Chino2")); // Chino2

	auto bone_bodyshell = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, VBone::vNames[VBone::bodyshell].c_str());

	att_veh_to_veh(rage::joaat("DUKES"), vehicle, VehicleColoursMatte::COLOR_MATTE_ORANGE, VehicleColoursMatte::COLOR_MATTE_ORANGE, 0, 0.3500f, 0.2200f, 3.5500f, 0, 0, false, bone_bodyshell);

	VEHICLE::SET_VEHICLE_COLOURS(vehicle, VehicleColoursMatte::COLOR_MATTE_ORANGE, VehicleColoursMatte::COLOR_MATTE_ORANGE);

	printf("spawned ChinoODeath\n");
}
void FunnyVehicles::RVBuilding()
{
	Vehicle vehicle = spawnVehicle(rage::joaat("Journey")); // Journey

	auto bone_bodyshell = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, VBone::vNames[VBone::bodyshell].c_str());

	att_veh_to_veh(rage::joaat("Journey"), vehicle, VehicleColoursClassic::COLOR_CLASSIC_PURE_WHITE, VehicleColoursClassic::COLOR_CLASSIC_PURE_WHITE, 0, 0, 2.2560f, 0, 0, 0, false, bone_bodyshell, true);
	att_veh_to_veh(rage::joaat("Journey"), vehicle, VehicleColoursClassic::COLOR_CLASSIC_PURE_WHITE, VehicleColoursClassic::COLOR_CLASSIC_PURE_WHITE, 0, 0, 2.2560f * 2.0f, 0, 0, 0, false, bone_bodyshell, true);

	VEHICLE::SET_VEHICLE_COLOURS(vehicle, VehicleColoursClassic::COLOR_CLASSIC_PURE_WHITE, VehicleColoursClassic::COLOR_CLASSIC_PURE_WHITE);

	printf("spawned RVBuilding\n");
}
