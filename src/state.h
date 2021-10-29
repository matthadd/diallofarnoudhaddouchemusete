
namespace state {

  enum GameStatus {
    PLAYING,
    WON,
    LOST,
    WAIT
  };

  /// class Position - 
  class Position {
    // Attributes
  private:
    int x;
    int y;
    // Operations
  public:
    Position (int x = 0, int y = 0);
    ~Position ();
    void move (int inc_x, int inc_y);
    void changePlace (int newX, int newY);
    int getX ();
    int getY ();
    void setX (int newX);
    void setY (int newY);
  };

  /// class UnitFactory - 
  class UnitFactory {
    // Operations
  public:
    UnitFactory ();
    ~UnitFactory ();
    /// crée une unité 
    /// @param typeUnitID		(???) 
    /// @param position		(???) 
    Unit* createUnit ();
  };

  /// class Building - 
  class Building {
    // Attributes
  protected:
    Position position;
    /// vaut 0 si le batiment est neutre, 1 si le joueur 1 contrôle, 2 si c'est le jou
    int controler;
    /// quantité de mana généré
    int amountMana;
    /// quantité d'hp généré
    int amountHp;
    /// identification building
    int buildingID;
    /// 

    std::string typeID;
    // Operations
  public:
    void setBuildingID (int buildingID);
    int getBuildingID ();
    Position getPostion ();
    int getAmountMana ();
    void setAmountMana (int newAmountMana);
    int getAmountHP ();
    void setAmountHP (int newAmountHP);
    std::string getTypeID ();
    void setTypeID (std::string newTypeID);
  };

  /// class Unit - 
  class Unit {
    // Attributes
  protected:
    /// nombres de combattants dans l'unité
    int size;
    /// position de l'unité sur la grille
    Position positions;
    /// 

    int singleUnitHp;
    /// Points de santés de l'unité complète
    int globalHp;
    /// Portée d'attaque de l'unité
    int attackrange;
    /// Vision maximale de l'unité
    int sightRange;
    /// Dégats infligé par un combattant de l'unité
    int singleUnitDamage;
    /// Dégats infligés par l'unité complète
    int globalDamage;
    /// Déplacement maximale de l'unité
    int moveRange;
    /// identification unité
    int unitID;
    /// identification type d'unité
    std::string typeUnit;
    /// Valeur statique permettant de créer les id des unités
    static int globalID;
    // Operations
  public:
    void init ();
    /// incrémente les attributs par les paramètres 
    /// @param i		(???) 
    /// @param j		(???) 
    bool move ();
    /// change les attributs i,j du joeur par les paramètres
    /// @param i		(???) 
    /// @param j		(???) 
    bool place ();
    int attack (Position position);
    Position getPosition ();
    void setPosition (int x, int y);
  };

  /// class Player - 
  class Player {
    // Attributes
  private:
    /// statut du joueur
    GameStatus status;
    /// Collection des batiments controlés par le joueur.
    std::map<int buildingID, Building building> buildings;
    /// Couleur attribuée au joueur
    std::string  color ;
    /// Fabrique d'unité
    UnitFactory unitFactory;
    /// Nom du joueur
    std::string name ;
    /// Collection de toutes les unités du joueur.
    std::map<int unitID, Unit unit> army;
    /// Quantité de mana du joueur
    int mana;
    // Operations
  public:
    /// constructeur
    Player ();
    ~Player ();
    /// méthode pour faire attaquer une unité à la position indiqué
    /// @param position		(???) 
    /// @param unitID		(???) 
    int attack ();
    /// Déplacer une unité vers la position indiquée.
    /// @param position		(???) 
    /// @param unitID		(???) 
    int move ();
    Building getBuildings (int buildingID = 0);
    void addBuilding (int buildingID = 0);
    void removeBuilding (int buildingID = 0);
    std::string getColor ();
    void setColor (std::string color);
    UnitFactory getUnitFactory ();
    void setName (std::string name);
    std::string getName ();
    void setStatus (GameStatus status);
    GameStatus getStatus ();
    Unit getUnit (int unitID = 0);
  };

  enum Playing {
    NO_PLAYER,
    PLAYER_1,
    PLAYER_2,
    END_GAME
  };

  /// class State - 
  class State {
    // Attributes
  private:
    Player player_1;
    Player player_2;
    /// Numéro du tour en cou cour
    int turn;
    Playing playing;
    // Operations
  public:
    /// constructeur
    State ();
    ~State ();
    void init ();
    void initPlayer1 ();
    void initPlayer2 ();
    void IncrementTurn ();
    /// change the player name playing
    void ChangePlaying ();
    Player getPlayer (int playerID);
    void setPlayer (Player newPlayer, int playerID);
    int getTurn ();
    void setTurn (int turn);
    Playing getPlaying ();
    void setPlaying (Playing playing);
  };

  enum Playing {
    NO_PLAYER,
    PLAYER_1,
    PLAYER_2,
    END_GAME
  };

  /// class Environment - 
  class Environment {
    // Associations
    state::Position* unnamed;
    // Attributes
  protected:
    int typeID;
    std::vector<Position> allPositions;
    // Operations
  public:
    int getTypeID ();
    void setTypeID (int newTypeID);
  };

  /// class Dwarf - 
  class Dwarf : public Unit {
    // Attributes
  private:
    std::string typeUnit;
    int sightRange;
    int moveRange;
    int singleUnitHp;
    int singleUnitDamage;
    // Operations
  public:
    Dwarf ();
    ~Dwarf ();
  };

  /// class Wizard - 
  class Wizard : public Unit {
    // Attributes
  private:
    std::string typeUnit;
    int sightRange;
    int singleUnitHp;
    int singleUnitDamage;
    int moveRange;
    // Operations
  public:
    /// constructeur
    Wizard ();
    /// destructeur
    ~Wizard ();
  };

  /// class Bat - 
  class Bat : public Unit {
    // Attributes
  private:
    std::string typeUnit;
    /// vision max de l'unité
    int  sightRange;
    /// deplacement max de l'unité
    int moveRange ;
    /// degats ifligé par un combatant de l'unité
    int singleUnitDamage;
    /// pv de un element de l'unité
    int singleUnitHp;
    // Operations
  public:
    Bat ();
    ~Bat ();
  };

  /// class Knight - 
  class Knight : public Unit {
    // Attributes
  private:
    std::string typeUnit;
    int sightRange;
    int moveRange;
    int singleUnitHp;
    int singleUniteDamage;
    // Operations
  public:
    Knight ();
    ~Knight ();
  };

  /// class Goblin - 
  class Goblin : public Unit {
    // Attributes
  private:
    std::string typeUnit;
    int moveRange ;
    int sightRange;
    int singleUnitDamage;
    int singleUnitHp;
    // Operations
  public:
    Goblin ();
    ~Goblin ();
  };

  /// class Golem - 
  class Golem : public Unit {
    // Attributes
  private:
    std::string typeUnit;
    int sightRange;
    int moveRange;
    int singleUnitHp;
    int singleUnitDamage;
    // Operations
  public:
    Golem ();
    ~Golem ();
  };

  /// class ManaMine - 
  class ManaMine : public Building {
    // Attributes
  private:
    std::string typeID;
    // Operations
  public:
    /// constructeur
    ManaMine ();
    /// destructeur
    ~ManaMine ();
  };

  /// class Town - 
  class Town : public Building {
    // Attributes
  private:
    std::string typeID;
    // Operations
  public:
    /// constructeur
    Town ();
    /// destructeur
    ~Town ();
  };

  /// class TrainingCamp - 
  class TrainingCamp : public Building {
    // Attributes
  private:
    std::string typeID;
    // Operations
  public:
    /// constructeur
    TrainingCamp ();
    /// destructeur
    ~TrainingCamp ();
  };

  /// class Mountain - 
  class Mountain : public Environment {
    // Attributes
  private:
    std::string type;
    // Operations
  public:
    /// constructeur
    Mountain ();
    /// destructeur
    ~Mountain ();
  };

  /// class Forest - 
  class Forest : public Environment {
    // Attributes
  private:
    std::string type;
    // Operations
  public:
    /// constructeur
    Forest ();
    /// destructeur
    ~Forest ();
  };

  /// class Plain - 
  class Plain : public Environment {
    // Attributes
  public:
    std::string type;
    // Operations
  public:
    /// constructeur
    Plain ();
    /// destructeur
    ~Plain ();
  };

  /// class Headquarter - 
  class Headquarter : public Building {
    // Attributes
  private:
    std::string typeID;
    // Operations
  public:
    /// constructeur
    Headquarter ();
    ~Headquarter ();
  };

};

