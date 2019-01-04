#ifndef SERVERPROPERTIES_H
#define SERVERPROPERTIES_H
#include <QString>

class ServerProperties
{
public:

    static ServerProperties* get_instance();
    void load_server_properties();
    void save_to_disk();

    static bool is_created();

    QString get_gen_sets();
    QString get_motd();
    int get_op_level();
    bool get_broadcast_console();
    bool get_nether();
    bool get_query();
    int get_query_port();
    bool get_flight();
    QString get_level_name();
    int get_port();
    int get_world_size();
    QString get_level_type();
    bool get_rcon();
    int get_rcon_port();
    QString get_rcon_password();
    bool get_force_game_mode();
    QString get_seed();
    QString get_ip();
    int get_build_height();
    int get_view_distance();
    bool get_npc();
    bool get_whitelist();
    bool get_animals();
    bool get_monsters();
    bool get_generate_structs();
    bool get_snooper();
    bool get_hardcore();
    bool get_online_mode();
    bool get_prevent_proxy();
    QString get_resourcepack();
    QString get_resourcepack_sha_1();
    bool get_pvp();
    int get_difficulty();
    bool get_command_block();
    int get_idle_timeout();
    int get_game_mode();
    int get_network_compression();
    int get_max_players();
    int get_tick_time();

    void set_gen_sets (QString gen_sets);
    void set_motd (QString motd);
    void set_op_level (int op_level);
    void set_broadcast_console (bool broadcast_console);
    void set_nether (bool nether);
    void set_query (bool query);
    void set_query_port (int query_port);
    void set_flight (bool flight);
    void set_level_name (QString level_name);
    void set_port (int port);
    void set_world_size (int world_size);
    void set_level_type (QString level_type);
    void set_rcon (bool rcon);
    void set_rcon_port (int rcon_port);
    void set_rcon_password (QString rcon_password);
    void set_force_game_mode (bool force_gamemode);
    void set_seed (QString seed);
    void set_ip (QString ip);
    void set_build_height (int build_height);
    void set_view_distance (int view_distance);
    void set_npc (bool npc);
    void set_whitelist (bool whitelist);
    void set_animals (bool animals);
    void set_monsters (bool monsters);
    void set_generate_structs (bool generate_structs);
    void set_snooper (bool snooper);
    void set_hardcore (bool hardcore);
    void set_online_mode (bool online_mode);
    void set_prevent_proxy (bool prevent_proxy);
    void set_resourcepack (QString resource_pack);
    void set_resourcepack_sha_1 (QString resourcepack_sha_1);
    void set_pvp (bool pvp);
    void set_difficulty (int difficulty);
    void set_command_block (bool command_block);
    void set_idle_timeout (int idle_timeout);
    void set_game_mode (int game_mode);
    void set_network_compression (int network_compression);
    void set_max_players (int max_players);
    void set_tick_time (int tick_time);


private:
    ServerProperties();
    void apply_default_values();

    static bool _is_created;

    QString _gen_sets;
    QString _motd;
    int _op_level;
    bool _broadcast_console;
    bool _nether;
    bool _query;
    int _query_port;
    bool _flight;
    QString _level_name;
    int _port;
    int _world_size;
    QString _level_type;
    bool _rcon;
    int _rcon_port;
    QString _rcon_password;
    bool _force_game_mode;
    QString _seed;
    QString _ip;
    int _build_height;
    int _view_distance;
    bool _npc;
    bool _whitelist;
    bool _animals;
    bool _monsters;
    bool _generate_structs;
    bool _snooper;
    bool _hardcore;
    bool _online_mode;
    bool _prevent_proxy;
    QString _resourcepack;
    QString _resourcepack_sha_1;
    bool _pvp;
    int _difficulty;
    bool _command_block;
    int _idle_timeout;
    int _game_mode;
    int _network_compression;
    int _max_players;
    int _tick_time;
};

bool string_to_bool (std::string str);
std::string bool_to_string (bool val);

int string_to_int (std::string str);
std::string int_to_string (int val);

#endif // SERVERPROPERTIES_H


























