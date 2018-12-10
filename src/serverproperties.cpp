#include "serverproperties.h"
#include "properties.h"
#include "settings.h"
#include <string>
#include <QFile>

bool ServerProperties::_is_created = false;

ServerProperties::ServerProperties()
{
    load_server_properties();
}


void ServerProperties::load_server_properties()
{
    QString props_filename = Settings::getInstance()->get_working_dir().append("/server.properties");
    if (QFile (props_filename).exists())
    {
        Properties props = Properties (std::string(props_filename.toLocal8Bit().data()));

        set_gen_sets (QString (props.getValue(std::string ("generator-settings")).c_str()));
        set_motd (QString (props.getValue(std::string ("motd")).c_str()));
        set_op_level (string_to_int (props.getValue(std::string ("op-permission-level"))));
        set_broadcast_console (string_to_bool (props.getValue(std::string ("broadcast-console-to-ops"))));
        set_nether (string_to_bool (props.getValue(std::string ("allow-nether"))));
        set_query (string_to_bool (props.getValue(std::string ("enable-query"))));
        if (props.contains(std::string("query.port"))) set_query_port(string_to_int (props.getValue(std::string ("query.port"))));
        else set_query_port(0);
        set_flight (string_to_bool(props.getValue(std::string ("allow-flight"))));
        set_level_name (QString(props.getValue(std::string ("level-name")).c_str()));
        set_port (string_to_int (props.getValue(std::string ("server-port"))));
        set_world_size (string_to_int (props.getValue(std::string ("max-world-size"))));
        set_level_type(QString (props.getValue(std::string ("level-type")).c_str()));
        set_rcon (string_to_bool (props.getValue(std::string ("enable-rcon"))));
        if (props.contains(std::string("rcon.port"))) set_rcon_port(string_to_int (props.getValue(std::string ("rcon.port"))));
        else set_rcon_port(0);
        if (props.contains(std::string("rcon.password"))) set_rcon_password(QString (props.getValue(std::string ("query.port")).c_str()));
        else set_rcon_password(QString (""));
        set_force_game_mode (string_to_bool (props.getValue(std::string ("force-gamemode"))));
        set_seed (QString (props.getValue(std::string ("level-seed")).c_str()));
        set_ip (QString (props.getValue(std::string ("server-ip")).c_str()));
        set_build_height (string_to_int (props.getValue(std::string ("max-build-height"))));
        set_view_distance (string_to_int (props.getValue(std::string ("view-distance"))));
        set_npc (string_to_bool(props.getValue(std::string ("spawn-npcs"))));
        set_whitelist (string_to_bool(props.getValue(std::string ("white-list"))));
        set_animals (string_to_bool(props.getValue(std::string ("spawn-animals"))));
        set_monsters (string_to_bool(props.getValue(std::string ("spawn-monsters"))));
        set_generate_structs (string_to_bool(props.getValue(std::string ("generate-structures"))));
        set_snooper (string_to_bool(props.getValue(std::string ("snooper-enabled"))));
        set_hardcore (string_to_bool(props.getValue(std::string ("hardcore"))));
        set_online_mode (string_to_bool(props.getValue(std::string ("online-mode"))));
        set_prevent_proxy (string_to_bool(props.getValue(std::string ("prevent-proxy-connections"))));
        set_resourcepack (QString (props.getValue(std::string ("resource-pack")).c_str()));
        set_resourcepack_sha_1 (QString (props.getValue(std::string ("resource-pack-sha1")).c_str()));
        set_pvp (string_to_bool(props.getValue(std::string ("pvp"))));
        set_difficulty (string_to_int (props.getValue(std::string ("difficulty"))));
        set_command_block (string_to_bool(props.getValue(std::string ("enable-command-block"))));
        set_idle_timeout (string_to_int (props.getValue(std::string ("player-idle-timeout"))));
        set_game_mode (string_to_int (props.getValue(std::string ("gamemode"))));
        set_network_compression (string_to_int (props.getValue(std::string ("network-compression-threshold"))));
        set_max_players (string_to_int (props.getValue(std::string ("max-players"))));
        set_tick_time (string_to_int (props.getValue(std::string ("max-tick-time"))));

    }
    else apply_default_values();

}

void ServerProperties::apply_default_values()
{
    set_gen_sets(QString(""));
    set_motd(QString(""));
    set_op_level(1);
    set_broadcast_console(false);
    set_nether(false);
    set_query(false);
    set_query_port(0);
    set_flight(false);
    set_level_name(QString(""));
    set_port(0);
    set_world_size(0);
    set_level_type(QString("DEFAULT"));
    set_rcon(false);
    set_rcon_port(0);
    set_rcon_password(QString(""));
    set_force_game_mode(false);
    set_seed(QString(""));
    set_ip(QString(""));
    set_build_height(0);
    set_view_distance(0);
    set_npc(false);
    set_whitelist(false);
    set_animals(false);
    set_monsters(false);
    set_generate_structs(false);
    set_snooper(false);
    set_hardcore(false);
    set_online_mode(false);
    set_prevent_proxy(false);
    set_resourcepack(QString(""));
    set_resourcepack_sha_1(QString(""));
    set_pvp(false);
    set_difficulty(0);
    set_command_block(false);
    set_idle_timeout(0);
    set_game_mode(0);
    set_network_compression(0);
    set_max_players(0);
    set_tick_time(0);
}

void ServerProperties::save_to_disk()
{
    Properties props;

    props.setValue (std::string ("generator-settings"), std::string(get_gen_sets().toLocal8Bit().data()));
    props.setValue (std::string ("motd"), std::string(get_motd().toLocal8Bit().data()));
    props.setValue (std::string ("op-permission-level"), int_to_string(get_op_level()));
    props.setValue (std::string ("broadcast-console-to-ops"), bool_to_string(get_broadcast_console()));
    props.setValue (std::string ("allow-nether"), bool_to_string(get_nether()));
    props.setValue (std::string ("enable-query"), bool_to_string(get_query()));
    if (get_query())
    {
        props.setValue (std::string ("query.port"), int_to_string(get_query_port()));
    }
    props.setValue (std::string ("allow-flight"), bool_to_string(get_flight()));
    props.setValue (std::string ("level-name"), std::string(get_level_name().toLocal8Bit().data()));
    props.setValue (std::string ("server-port"), int_to_string(get_port()));
    props.setValue (std::string ("max-world-size"), int_to_string(get_world_size()));
    props.setValue (std::string ("level-type"), std::string(get_level_type().toLocal8Bit().data()));
    props.setValue (std::string ("enable-rcon"), bool_to_string(get_rcon()));
    if (get_rcon())
    {
        props.setValue (std::string ("rcon.port"), int_to_string(get_rcon_port()));
        props.setValue (std::string ("rcon.password"), std::string(get_rcon_password().toLocal8Bit().data()));
    }
    props.setValue (std::string ("force-gamemode"), bool_to_string(get_force_game_mode()));
    props.setValue (std::string ("level-seed"), std::string(get_seed().toLocal8Bit().data()));
    props.setValue (std::string ("server-ip"), std::string(get_ip().toLocal8Bit().data()));
    props.setValue (std::string ("max-build-height"), int_to_string(get_build_height()));
    props.setValue (std::string ("view-distance"), int_to_string(get_view_distance()));
    props.setValue (std::string ("spawn-npcs"), bool_to_string(get_npc()));
    props.setValue (std::string ("white-list"), bool_to_string(get_whitelist()));
    props.setValue (std::string ("spawn-animals"), bool_to_string(get_whitelist()));
    props.setValue (std::string ("spawn-monsters"), bool_to_string(get_monsters()));
    props.setValue (std::string ("generate-structures"), bool_to_string(get_generate_structs()));
    props.setValue (std::string ("snooper-enabled"), bool_to_string(get_snooper()));
    props.setValue (std::string ("hardcore"), bool_to_string(get_hardcore()));
    props.setValue (std::string ("online-mode"), bool_to_string(get_online_mode()));
    props.setValue (std::string ("prevent-proxy-connections"), bool_to_string(get_prevent_proxy()));
    props.setValue (std::string ("resource-pack"), std::string(get_resourcepack().toLocal8Bit().data()));
    props.setValue (std::string ("resource-pack-sha1"), std::string(get_resourcepack_sha_1().toLocal8Bit().data()));
    props.setValue (std::string ("pvp"), bool_to_string(get_pvp()));
    props.setValue (std::string ("difficulty"), int_to_string(get_difficulty()));
    props.setValue (std::string ("enable-command-block"), bool_to_string(get_command_block()));
    props.setValue (std::string ("player-idle-timeout"), int_to_string(get_idle_timeout()));
    props.setValue (std::string ("gamemode"), int_to_string(get_game_mode()));
    props.setValue (std::string ("network-compression-threshold"), int_to_string(get_network_compression()));
    props.setValue (std::string ("max-players"), int_to_string(get_max_players()));
    props.setValue (std::string ("max-tick-time"), int_to_string(get_tick_time()));

    props.storeToFile (std::string (Settings::getInstance()->get_working_dir().append(QString("/server.properties")).toLocal8Bit().data()));
}


ServerProperties* ServerProperties::getInstance()
{
    static ServerProperties* _instance = new ServerProperties();
    _is_created = true;
    return _instance;
}

bool ServerProperties::is_created()
{
    return _is_created;
}


QString ServerProperties::get_gen_sets (){ return _gen_sets;}
QString ServerProperties::get_motd (){ return _motd;}
int ServerProperties::get_op_level (){ return _op_level;}
bool ServerProperties::get_broadcast_console (){return _broadcast_console;}
bool ServerProperties::get_nether (){ return _nether;}
bool ServerProperties::get_query (){ return _query;}
int ServerProperties::get_query_port (){ return _query_port;}
bool ServerProperties::get_flight (){ return _flight;}
QString ServerProperties::get_level_name (){ return _level_name;}
int ServerProperties::get_port (){return _port;}
int ServerProperties::get_world_size (){return _world_size;}
QString ServerProperties::get_level_type (){ return _level_type;}
bool ServerProperties::get_rcon (){ return _rcon;}
int ServerProperties::get_rcon_port (){ return _rcon_port;}
QString ServerProperties::get_rcon_password (){ return _rcon_password;}
bool ServerProperties::get_force_game_mode (){ return _force_game_mode;}
QString ServerProperties::get_seed (){ return _seed;}
QString ServerProperties::get_ip (){return _ip;}
int ServerProperties::get_build_height()  {return _build_height;}
int ServerProperties::get_view_distance() {return _view_distance;}
bool ServerProperties::get_npc() {return _npc;}
bool ServerProperties::get_whitelist() {return _whitelist;}
bool ServerProperties::get_animals() {return _animals;}
bool ServerProperties::get_monsters() {return _monsters;}
bool ServerProperties::get_generate_structs() {return _generate_structs;}
bool ServerProperties::get_snooper() {return _snooper;}
bool ServerProperties::get_hardcore() {return _hardcore;}
bool ServerProperties::get_online_mode() {return _online_mode;}
bool ServerProperties::get_prevent_proxy() {return _prevent_proxy;}
QString ServerProperties::get_resourcepack() {return _resourcepack;}
QString ServerProperties::get_resourcepack_sha_1 () {return _resourcepack_sha_1;}
bool ServerProperties::get_pvp() {return _pvp;}
int ServerProperties::get_difficulty() {return _difficulty;}
bool ServerProperties::get_command_block (){return _command_block;}
int ServerProperties::get_idle_timeout() {return _idle_timeout;}
int ServerProperties::get_game_mode() {return _game_mode;}
int ServerProperties::get_network_compression() {return _network_compression;}
int ServerProperties::get_max_players() {return _max_players;}
int ServerProperties::get_tick_time() {return _tick_time;}

void ServerProperties::set_gen_sets(QString gen_sets) {_gen_sets = gen_sets;}
void ServerProperties::set_motd(QString motd) {_motd = motd;}
void ServerProperties::set_op_level(int op_level) {_op_level = op_level;}
void ServerProperties::set_broadcast_console(bool broadcast_console) {_broadcast_console = broadcast_console;}
void ServerProperties::set_nether(bool nether) {_nether = nether;}
void ServerProperties::set_query(bool query) {_query = query;}
void ServerProperties::set_query_port(int query_port) {_query_port = query_port;}
void ServerProperties::set_flight(bool flight) {_flight = flight;}
void ServerProperties::set_level_name(QString level_name) {_level_name = level_name;}
void ServerProperties::set_port(int port) {_port = port;}
void ServerProperties::set_world_size (int world_size) {_world_size = world_size;}
void ServerProperties::set_level_type (QString level_type) {_level_type = level_type;}
void ServerProperties::set_rcon (bool rcon) {_rcon = rcon;}
void ServerProperties::set_rcon_port (int rcon_port) {_rcon_port = rcon_port;}
void ServerProperties::set_rcon_password (QString rcon_password) {rcon_password = rcon_password;}
void ServerProperties::set_force_game_mode (bool force_game_mode) {_force_game_mode = force_game_mode;}
void ServerProperties::set_seed (QString seed) {_seed = seed;}
void ServerProperties::set_ip (QString ip) {_ip = ip;}
void ServerProperties::set_build_height (int build_height) {_build_height = build_height;}
void ServerProperties::set_view_distance(int view_distance) {_view_distance = view_distance;}
void ServerProperties::set_npc (bool npc) {_npc = npc;}
void ServerProperties::set_whitelist (bool whitelist) {_whitelist = whitelist;}
void ServerProperties::set_animals (bool animals) {_animals = animals;}
void ServerProperties::set_monsters(bool monsters) {_monsters = monsters;}
void ServerProperties::set_generate_structs(bool generate_structs) {_generate_structs = generate_structs;}
void ServerProperties::set_snooper (bool snooper) {_snooper = snooper;}
void ServerProperties::set_hardcore (bool hardcore) {_hardcore = hardcore;}
void ServerProperties::set_online_mode (bool online_mode) {_online_mode = online_mode;}
void ServerProperties::set_prevent_proxy (bool prevent_proxy) {_prevent_proxy = prevent_proxy;}
void ServerProperties::set_resourcepack (QString resourcepack) {_resourcepack = resourcepack;}
void ServerProperties::set_resourcepack_sha_1 (QString resourcepack_sha_1) {_resourcepack_sha_1 = resourcepack_sha_1;}
void ServerProperties::set_pvp (bool pvp) {_pvp = pvp;}
void ServerProperties::set_difficulty (int difficulty) {_difficulty = difficulty;}
void ServerProperties::set_command_block (bool command_block) {_command_block = command_block;}
void ServerProperties::set_idle_timeout (int idle_timeout) {_idle_timeout = idle_timeout;}
void ServerProperties::set_game_mode (int game_mode) {_game_mode = game_mode;}
void ServerProperties::set_network_compression(int network_compression) {_network_compression = network_compression;}
void ServerProperties::set_max_players (int max_players) {_max_players = max_players;}
void ServerProperties::set_tick_time (int tick_time) {_tick_time = tick_time;}










bool string_to_bool(std::string str)
{
    return !str.compare(std::string ("true"));
}

std::string bool_to_string(bool val)
{
    if (val) return std::string("true");
    return std::string ("false");
}

int string_to_int (std::string str)
{
    return std::stoi (str);
}

std::string int_to_string (int val)
{
    return std::to_string(val);
}







