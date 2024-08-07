#include <tldUtils.h>
#include <tldSprite.h>
#include <tldSpriteAnimation.h>

using namespace nudny;

bool tldSprite::Load( tson::Tile& t_tile, Resources& t_resources, std::string t_dir, glm::vec2 t_map_grid_size ) {
	m_tile 		= t_tile;
	tson::Rect r 	= tldUtils::GetCorrectDrawingRectangle( m_tile.getDrawingRect(), t_map_grid_size );
	glm::vec2 s 	= tldUtils::GetCorrectTileSize( r, m_tile.getTileSize(), t_map_grid_size );
	float w2	= s.x*0.5f;
	float h2	= s.y*0.5f;
	std::string t	= t_dir.append( m_tile.getTileset()->getImage() );
	int tex_id	= t_resources.textures.Load( t );
	
	m_gid 	= m_tile.getGid();
	SetSize( s.x, s.y );
	SetTexture( &t_resources.textures.GetRef( tex_id ) );
	SetTextureCoords( r.x, r.y, r.width, r.height );
	collide = false;

	for( auto o : m_tile.getObjectgroup().getObjects()) {
		// if object is polygon
		if( o.getPolygons().size() > 2 ) {	
			tson::Vector2i o_local_offset = o.getPosition();
			std::vector<glm::vec2> tmp_v;
			for( auto v : o.getPolygons() ) {
				tmp_v.push_back( glm::vec2( v.x-w2+o_local_offset.x, v.y-h2+o_local_offset.y  ));
			}
			collide = true;
			SetVertices( tmp_v );
		} else if( o.isEllipse() ) {
		} else {
			tson::Vector2i tmp_size = o.getSize();
			tson::Vector2i tmp_pos	= o.getPosition();
			if( tmp_size.x != 0 && tmp_size.y != 0 ) {
				float tw2 = tmp_size.x/2;
				float th2 = tmp_size.y/2;

				float tx = tmp_pos.x/2;
				float ty = tmp_pos.y/2;
						
				std::vector<glm::vec2> tmp_v;
				tmp_v.push_back( glm::vec2(-tw2 + tx, -th2 + ty));
				tmp_v.push_back( glm::vec2(-tw2 + tx ,th2 + ty));
				tmp_v.push_back( glm::vec2(tw2 + tx,th2 + ty ));
				tmp_v.push_back( glm::vec2(tw2 + tx ,-th2 + ty));
				collide = true;
				SetVertices( tmp_v );
			}
		}			
	}
	if( m_tile.getObjectgroup().getObjects().size() == 0 ) {
		std::vector<glm::vec2> tmp_v;
	       	tmp_v.push_back( glm::vec2(-w2,-h2));
		tmp_v.push_back( glm::vec2(-w2,h2));
		tmp_v.push_back( glm::vec2(w2,h2));
		tmp_v.push_back( glm::vec2(w2,-h2));
		collide = false;
		SetVertices( tmp_v );
	}
	if( m_tile.getAnimation().size() > 0 ) {
		std::unique_ptr<tldSpriteAnimation> tmp( new tldSpriteAnimation() );
		tmp->Load( m_tile.getAnimation(), m_tile.getTileset(), t_map_grid_size );
		animation = std::move(tmp);
//		tldSpriteAnimation tmp_animation;
//		tmp_animation.Load( m_tile.getAnimation(), m_tile.getTileset(), t_map_grid_size );
//		animation.reset( &tmp_animation );
		//animation->Load( m_tile.getAnimation(), m_tile.getTileset(), t_map_grid_size );		
	}
	return true;
}

// I NEVER thought, that I will use dot "." and arrow "->" to tha same pointer object

/****#%%******##%%###*********###%%%##****************************************************************************************************#*************##################################*******************************************
**#%@@#*************#%%%%%%%%%%##**************************##******************************************************************************#*************####################################**********************************#*###**
@@@#*****************************************************#@%#********************************************##***********************#%#*****##*###**#*****#################*#####################**********************#%@@#***#***#####
**%@%#*************************************************#@@@#******************************************#%%#*********************##@@@%****##***********#***########*###%%*##################**###*******************#%@#*#@@%####******
****%@%#********************************************#%@%#*%@@%#************************************#@@#**********************#%@%#*#@#*#*##*******#*******###########*##@%######*#######*####*#####**************#@%#******#%@@@@%%%@@
******#@@%#**************************************#%@%#******#%@@%#*****************************##%@%#**********************#%@%#*#*##@%*#****####*##*****######*#####*#%@%@@%##*####################**********#%@%***********#**######
*********#%@@%#*******************************#%@%#*************#%@@%%#*****************##%%@@@@%#***********************#@@#*#*****#%@@%*********#******####*#*#*##%@@%####%%@%#*#**###*###**###########%%@@%#*****************###*##
*************#%@@%##********************##%@@@%#*********************#%%@@@@@%%%%%%%@@@@%%###**#%@@%#****#*********##*#%@%######%%%@@@@@@@@@@%%%%####****###***#%%@%%##*##*#*###%@@@@%%##########%%@@@@%%##*#*****************########
*****************##%%@@@@%%########%@@@@%%#*********************************########**************#%@@%##********#*#%@%##=:........................:-+##%@@%%@@%##*####*#***#*##*##*####%%%%%@@%%############**##************#########
*************************###########******#**********************************************************##%@@@@%@%%#-.............                ... ..........-#%%@%#*#%@#****#*****#*#####%%%##################%####***#*#**#########%
***#********#**********##***#*********************#*#**#****#***************#*****#********#######*######%@*:........... ..                     ..    ............:*@@%##%%@%%%%%%%%%%@%%##*#################%@@####################@@
************#####*#**#******#**************##***########################*###%##################**#**#%@*:... . .......                                        .. .....:*@@%##*##*###########*########*######@@@@%#################%@%%
*****######*#######********************#%##**********########*#####******#%@@%#*##############*##%@@#....... .........                                ..........  ........*@@%##*###########*#############%@@+:*@@%#############%@@#-:
########*#*##*#####*##*###***************#@@%#******#*##*#####***#****##@@@**@@#*#*##########*##@%=....                                                               ......:%%@#*#**###################%@@#::::-*@@%%########%@@%=:::
##***#**##%@@##***#**##*#####***#%#********#%@@%#***###**###*###*####%@@#=:::=%@%###########%@@@+......                                                               ........:@%@####################%%@%-:-:::::-+#@@@@@@@@@@#-:-:::
***#***#@@%%@%*#**##*#####*#***%@@@@%#*#**#%@@+*%@@%#############%@@@%+::::::::+%@@@@@@@@@@%#@@:.....  ..... ..................    ... ..... .    ............. ................*%@#################%@@%=::::::--:-::::::::::::-::::::
*****#@@@+::*@@%#*##****#****%@@*:-+%@@@@@%#=::::-=*%@@@@@@@@@@@@#+-:::::::::::::::-====-::-@@... .  ........................ .   ....... .. .    ...............................*@%@@%%%%%%%%@@@@@@#+:-::::::::-:::::::::--:::-::::::
*#%@@@#=:::::=%@@@%#****##%@@@*-:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::%@+.     ..:@@@@@@+-@:..%*.#%.:%@@@+.....:@-.+@@@@: ....@@@@%.=@:-@+..%%.%@@@@.........%@%**###%%##%=-:::::::::::::::::::::::::::::::::::::
@@%*-::::::::::-+%@@@@@@@%#=::::::::::::::::::::::::::::-:-===========-====-:-::::::::::::-@@:.     .. ..*%...=@=..%*.#%.#@-........:@=.%#.........@=....=@:-@@*.%%.@+............=@%+++++#***%-::::::::::::::::::::::::::::::::::::::
#::::::::::::::::::::::::::::::::::::::::=+#%%%@%%#####*#*++++++++***#@@@@@@*:::::::::::::-@@:...      ..*%...=@@%@@*.##..-*%@#.....:@-..+#@@-....:@%%%:.+@:-@%%@@%.%%%%:.........=@@*++==#***%-::::::::::::::::::::::::::::::::::--::
#::::::::::::::::::::::::::::::::=@%%#*++++++++++++++++++++++++++++++*@@@@@@*::::::::::::::@@#....    ...#%...+@:.:%*.%%.*@+#@*.....=@=.%#+%@-....:@-....*@:=@-.@%%:@#++-.........%%#=====#***%-:::::::::::::::::::::-:-::-:-:::-:-:::
*::::::::::::::::::::::::::::::::=%++++++++++++++++++++++++++++++++++*@@@@@@*::::::::::::::=%@=........ ..:...................... ...:......... ..........:..:...:..::.....   ...+@%======#***%-:::::::::::::::::::::-::++-:-:::::::::
*:::::::::::=%*::::::::::::::::::-%++++++++++++++++++++++++++++++++++*@@@@@@*:::::::::::::::=@@*....  .  ..   ................     ...........    ....    .................  ...+%%=======#***%-::::::::::::::::-::::::*%%=:::::::::::
+::::::::::+%##-:::::::::::::::::-%*+++++++++++++++++++++++++++++++++*@@@@@@*:::::::::::::::::%%@:....                                             ..                   ......:@@#+==+====#***%-:::::::::::::::-::::::*%*%*:::::::::::
+:::::::::+%+=#+:::::::::::::::::=%++++++++++++++++++++++++++++++++++#@@@@@@*::::::::::::::::::-%@@-.....                                                               ....:%@**+=+**====#***%-:::::::::::::----::::=%+=##-:-::::::::
+::::::::+%+=+*#:::::::::::-:::::-%++++++++++++++++++++++++++++++++++*@@@@@@+::::::::::::::-::::::#@@#......      ......                                      .....   ....*@%+=*#==+#=**==#***%-::::::::::-:-:-:-::--%*==*%--:::::::::
*:::::::+%+===+%=::::::::::::::::-%*++++++++++++**++++++%#+++++++*#%%%@@@@@@+:::::::::::::::::::::::-#@@%-.......  ......                             ................:#%%+===+#===#++#=++#***%-:::::::::-:--::::::-+%+==+%+::::::::::
#-:::::+%+====+#*::::::::::::::::=%*+*++++*#*+++++++++*#=*#+++++%#======*%@@+::::::::::::::::::::::--:::=@@*.............    .                        ............-*@%#**====+#+==#+*#+#+=#***%-::::::::--:---=:::::*%==+=##::::::::::
#+::::=%*======*%-:::::::::::::::-%*****+##+#*+++++++*#+==*#+++%*=========#@+-=*+-::::::::::::::::::::::*@%....+%%*=:..........  ...   ...  ..... ..........:+#@%*+%%***##====+==*+=+=#==+#***%-:::::-::-::-=#%#::::*#====+%+:::::::::
*%=::-##=======+%=:::::::::::::::-%*****#*==+#+++++**%*====##+*%+======+*##@%%+=*#:::::::::::::::::::::*%#..:*@*:::=*#%@@@#+=-::........ ........::-=+%@%#*-:#*+===#%***#%======+====+=++=#***%-:::::::--::=%#*%+:::*#====+##-::::::::
=##-:+%+========##:::::::::::::::-%****#*===+#******##======##*%*==+%@@@@@@@#===+%:::::::-:::::::::::=@%::#@#:-:::::::::::::::--+*##########*+=-::::::::::::-%*====+%#**#%+====++===+==++=#***@-:::::-----+%*+=#*:-:##=====+%*::::::::
=+%*:*#=========*%=::::::::::::::-%***#*=====#*****##========**+%@@@@@@@@@@#====#%##*+-:::::::::::-%@%%@*:-:-::::::::::::::::::::::::::::-:::::::---::::-:::-%*=====#%***#####%%%##########***@-::::::-:-*%*===%*-:=%+===+==+%=:-:::::
==*%+#*=====+===+%+::::::::::::::-%*##+=++==++#****#+=========#%###%%%%%#+====+%*=====+##-::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::=%+=====*%******%#++%*************%-::::::--#%+===+%*--%#+=======#%-::::::
===#%%*======+===##::::::::::::::-%##==+==+===##**#*===+**+==##=============*%*==========*#-:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::-#%+=+===*%@@@@%%+==+%%@@@@@@@@@@@@%-::::::-##+=====*%*%*=+==*+===+##-:::::
===+#%#+====+%===+%=:::::::::::::-%#+=+=:-*===+#%*#++==*:-*+*+%%#**+++*%%%%*=============-*%:-:::::::::::::::::::::::::::::::::-:::::::::::::::::::::::::::+%*====++*%--+%*===++%#+*++****+=-:::::--:-##=======+#%+====#=+====+#*:::::
=====++=====#++==+#*:::::::::::::-%+=++:::=+====*%#+==+=::=*+:::*++%*===================*%@@%+::-::::::::::::::::::::::::::::::::-::::::::::::::::----::::=%#=====++##-#%*=====+*%+::::::::::::::--:-##==========+=+=+#-:#+====+#*:-:-
=========+=*-=*===*%-:::::::*=::::##=+-::::++====++===+::::+-::::=##==================*-....-=##-:-:::::::::::::::::::::::::::::=+-::::::::::::::-:::-:--=%#+=======##%%++=======*%=-:::::::::::::::*#+=============*=:::-#=====+#*::-
==========#=:=*===+%=::::::=%#::::+#++::::::+++====+=*-::::::::::+@=======****+=====-*:..:@@@@@#%::::::::::::::::::::::::::::::+%%-:::::::::::::::::-:::-%#+==+##==+%%#====*+=====*%=-:::::::::::::+%+==+##=====+=#+::::::=#=====+%*-=
=========+*::=+===+#*::::::#%%-::-=%*-:::::::*======+=:::::::::=@@@=====*=.....=#===+=...%@@@%@@@-::::::::::::::::::::::::::::+%##-:::::::::::::::-::::-#%+===#=*+=+#*===+#-*+=====#%+-:-:::::::::-##===#-#++===+*:::::::::+*=====+%*=
+=======+#-::=*====*#-::::-%#%*:::-%*:::::::::+*=+=+*::::::::-#@@@@*===*.-%@@@@=.-*=*-..:@@%***%%=:::::::::::::::::::::::::::+%++%-::::::::-:::::-:::-:+%+===**:=#======**:::#======+##--:::::::::+%+==*=:+*===#+:::::::::::+*=+##*+%*
**+=====*+::::#+===+%=::::=%+*%-:::#+::::::::::-*+=*=:::::::+@@@@@@%==+--@@@@%#%=.*=++...%@****#@-:::::-=**##*-:::::::::::::+%+=+%=::::::::-:--:::::::-%*===+*:::#+====#=::::-+=======*%=::::::::-%*==+*::-#=+#::::::::::::::*%%%%*=*%
:+#=====*:::::*+====#*::::##=+%+:::*+::::::::::::-*#-::::::#@@@@@@@#==*:+@@@#***+.+==+:..-@#*%%%##*#%@@@@@@@@@@@+::::-:::::=%+===##--:::::::::--:::-::+%+===*::::=#===+*::::::++=======*%+::--:::*#===*=:::*#+:::::::::::::+%#++%#+*%#
::=#+==+*:::::=*====*%-::=%+==##-::+*:::::::::::::::::::::%@@@@@@@@%==+:-@@%****--*=-=+*+*##+======+@@@@@@@@@@@@%--:::::::=%+=++=+%*:::--:::::::::-::-%*==+*::::::*+==*-.::::::*=======+#%---:-:+%+==*+::::--::::::::::::*%*+==#%*##+=
:::=#==+=:::::-*+===+%+:-*#===*%=::**::::::::::::::::::::%@@@@@@@@@%===+.=@@#**-.*===-+*+==========+@@@@@@@@@@@@#:-:::-::+%*====+=*%=-:::-:::::::::::=%*+=#-::::::++=++::::::::-*=======+#*-:::=%*===*:::::::::::::::::=%*+===+#%%#===
::::=*=*=.:::::*+====%*:=%*===+%#:-#=:::::::::::::::::::#@@@@@@@@@@#===+-......:*===================*@@@@@@@@@@#:-:::-::+%*===*#+==#%--:::-:-::::::::=%*=*+:::::::-#=*::::::::::=*=======*%-::=%#===#-::::::::::::::::*%+=====+%%*====
:::::+**+::::::*+===+#*-##=+===*%=-#=::::::::::::::::::+@@@@@@@@@@@*-====*+--=++=========-============+*****+=#*::+%*-:=%*===#+++=++##---:-----::-:::*%++*:::::::::*#-:::::::::::=*======+##:+%*===*=::::::::::::::::##+=======**=====
::::::+%#::::::*+===+%*+%++====+##-#=:::::::::::::::::-%@@@@@@@@@@%=======================#+================+%*-:+%#%+-##+==#*::#@%%%%@%%%%%%%%+:-:-#%+=++::::::::::.:::::::::::::=*======*%#%*===*=::::::::::::::::##================
:::::::=+::::::*=====#%%#=+=====+%*#-:::::::::::::::::=@@@@@@@@@@@+====================#*=+%%+============+%#-::=%#+*%*%+==*#::-%#%%%%%%%%%#**#*::=%#+==#-:::::::::::::::::::::::::+++=====##+==+#-::::::::::::::::##=================
:::::::::::::::=+===+#%%*====+===*%%=::::::::::::::-%%%%@@@@@@@@@+==========================%--=*#%%%%%%#+-:-::-#%+=+%%#==+%-::=#::+*###*=-::-#@%%@#=+=**:::::::::::::::::::::::::::*==========**:::::::::::::::::##==================
::::::::::::::::#====#%#+===*%+==+#%-::::::::::::::%++++#@@@@@@#============================%--:::::::::::::-::*%+===#%*==#-:::-#::::::::::::-%=-::-#%+*::::::::::::::::::::::::::::-*=======+#-:::::::::::::::::##+==================
::::::::::::::::*+===*%*===+#-*=+=*%=::::::::::::::%+++++#+++%========+=====================%=::::::::::::::::+%*====+#+=*+::::-#-:::::::::::-%%%%+:-#*.::::::::::::::::::::::::::::.*+====+*=.::...:.:.:::.:.:.*#========+===========
::::::::::::::::-*===+%====*+:*+==+##:::::::::::::=#+++++#+++#========**+===================**-::::::::::::::=%*========+*::::::%-:::::::::::+@%%%%::#%#****************************************######*########%#+==+=+=+*===========+
:::::::::::::::::#+===+====#::-*===+%=::::::::::::#*+++++*+++%=-=-=*--*+-=-==================%-:-:::::::::::=%+=========*=::=#@%%-::::::::::-*%%%*-:-%=============================================*%*========*#+======***+========+*-
:::::::::::::::::=#=======*+:::#====#*::::::::::::#*+++++*+++#-====*-=#======================%=::::::::::::=%*+==##++===##%*====%-:::::::::::*+:::=#%+============================================*%%+======+%#=+====+#=:*+=======#=.:
::::::::::::::::::*=======#::::*+===*#-:::::::::::%*+++++*+++#-=-==*==#=-====================*+::-::::::::-#*===**:+#+%#+=======%-:::::::::::##***==============================================+##*%+=====*%*=+====+#-::+*=====+*-:::
::::::::::::::::::-#+====+*::::+*===+%-:::::::::::%*+++++*+++%-==-==+=+%=====================**::-:::::-:-*%+==+*:::-%+=========%=:::::::::-=%+================================================#%+=*%====+##+====+=+*::::-#====*+:::::
:::::::::::::::::::+*====*-::::-*===+%=:::::::::::%*+=+++*++=%+===-=*==*#====================**::::::::::=%#===++:::-%#+=========+#%%%%%%%%%#*===============================================+%#===*%===#%*======+*+::::::*+==*-::::::
::::::::::::::::.:::*++=+*:::::-*===+%=::::-#%=:::##+++++*++++%=-====*==+%+==================*+::::::::::-%*===*-:::=%++*#*+===============================================================+##+=+==*%=+%#+=======*+:::::::=*=*-:::::::
:::::::::::::::::::::#*=*-::::::*===+%=----+%%#---=%+++++#=+++##-==-==*+-=##+==============-=%+=-::::::::-%+===*-:::=%+++++++********++======================++==========================*%#+======*%##+=======+++:::::::::+#-.:::::::
::::::::::::::::::::::*#*:::::::*===+%=---=##*%+---##++++*#+=*#%#=-====+*+=-=#%#+++++++==-=*%+==*%-::::-:=%*===*-::::##+++++++++++++++++++++******+++======+#%#============-=-========*%%#+========+#+=+=======++:::::::::::::::::::::
:::::::::::::::::::::::+=::::::-*===*#=---+%++#*----##+++++%@+++*%*======+%%##*+====-==%#%%%%%%=-**::-::-=%*===*-:::::+%%#++=++++++++++++++++++++++++++++*%%*#%*##############%####%%#*+=======================*::::::::::::::::::::::
:::::::::::::::::::::::::::::::-*===##==**%#==#%**+===*###%#+++++++*%%#*++*+++****#*====%+++++#*=**+#%%%%+%+==+*-::::::::::=+**%%%##*+++++++++++++++++++#%*+=##++++++++++++++++*#%*++========================*#:::::::::::::::::::::::
:::::::::::::::::::::::::::::::=*==+#*++=##+==*%*****+=+==%*++++===+++=+++=++++++++%====%+++++#*=*#=-===*%%+==+#-::::::::::::::=@@@@@@+++*##%%%%%%%#**#%*====#*++++++++==+=+*%#*+==========+**++==========++#=.:::::::::::::::::::::::
:::::::::::::::::::::::::::::::=*==+%*=+*#+===*%#######++=##+++++++=+===+++++++++++%+-==%#%%%###-=-=-===##%*===*-::::::::::::::=@@@@%@-:::::::::::::+%*+====+%@@%%%###****#%*+===========+#+:.-*=======+=+*=::::::::::::::::::::::::::
:::::::::::::::::::::::::::::::=*==+%+=*%+====+%*++++++++++#%%%%@%%%@%@@@@@@@@@@%%%%*=-====-=#@@*-==+#%#--%*===*-::::::::::::::+#++++%=::::::::::-*%*=======+%@@@@@@=::*%#+===+=======+#+::::::*+=======#-::::::::::::::::::::::::::::
:::::::::::::::::::::::::::::::=*==+%+*%*=====+%*+=+++++++++=++*%+++%+%@@@@@%+@@@@@@%========%@@@%=--::::-%*===*-::::::::::::::+#+++=%-::::::::=##+=========*%@@@@@@=*%+==========++#*-::::::::=+=====+*-:::::::::::::::::::::::::::::
:::::::::::::::::::::::::::::::+*==+%*%*======+%*=++++++++++++++%+++%+*@@@@@@%@@@@@%#%####%@@@@@@%=======##+===*-::::::::::::::+#+++=%=::::::*%*+===========*%@@@@@%#+==========+#+:::::::::::::+====+*:::::::::::::::::::::::::::::::
:::::::::::::::::::::::::::::::=*==+%%#=======+%*+++++++++=====+%+++%+=++++++*@@@@#%+++*#+++%@@@%%*+++++#%++==*=:::::::::::::::+#++++%=:::-##*==============#%@@@%%*==========**::::::::::::::.:*===++::::::::::::::::::::::::::::::::
:::::::::::::::::::::::::::::::=*==+%#+===*+==+%+++++++====+++++%++*%++=+++++*@@@@#%+++*#+++%@@%+%+++++*%*===#*::::::=*#=::::::+#++++%-:=##+=+==============*%@@%#+=========+*-:::::::::::::::::*+=*=:::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::*==+%+===+#*+=+%+=======++==+=+*#+++%+=++++++*@@@@#%+++##+++@@@*+%+++++*###**%=-==*##+**:::.-*#%#++++%*##+==================#%%%#+=========#=:::::::::::::::::::-##=::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::++=======*--*==#*+==+=+*+++++++*#++*%++++++++*@@@@#%+++##+++@@@*+%+++++=++++++++++=++*#++##*+**+#++++#%*+==========+========#%%#+=======+**:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:::::::::::::-+:::::::::::::::::=*=====+#-.:*+=##=+++#%%*=+=+++*#++*%++++****#@@@@#%+++##+++@@@++%+++++++++++====++======+=++++*#++#%#+=+=======+*=++=======#%#+======+**:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:::::::::::::-+::::::::::::::::::#+===+*-:::*+=##+++##+*%+==+==*#++*#=++*####%@@@@#%+++##+++@@@++%++=++===+++++=+++++++++++++++*#*%%*=========+*:::=+=======+#+=====+#+:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::+:::
::::::::::::::+:::::.::::::::::::=*==+*:::::*+=+%+=*%+=+%++=+==*#++*#==+++++=*@@@@#%*++##+++@@@++%++===*#***********+==+=+++++=*%%#+========+*:.:::=+=============+#+::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::-*:::
::::::::::::::+::::::::-::::--::::*++#::::::++=+#%+#*==+%+=====*#++*#=====+==*@@@@##*++*#+=+@@@++%+===+++*****#####*=+==+==++=+#%*==+======*=::::::-*==========+=**::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::-*:::
::::::::::::::==:::::::++:::-*::::-#*:::::::=*===#%#+==+%*=====*#++*#+=======+@@@@##*++**==+%@@++%+===+========+==+===++=====+##+=======++*::::::::.++=========**:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::.=+:::
:::::::-=:::::-*::-:::::*::::+=::::.:::::::::*+==+*+====*%+====+#++*#========+%@@@**#+=**=++%@@++%=====+********####*#+=====+##=========*+::::::::::-*========*-:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::=.+=:*/
