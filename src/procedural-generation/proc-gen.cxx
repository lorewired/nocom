#include "proc-gen.hxx"

using namespace procedural_generation;

void procedural_generation::connect_rooms(
    std::shared_ptr<map_node> src,
    std::shared_ptr<map_node> dst,
    node_dir dir
)
{
    // bidirectional connection
    switch (dir) {
        case TOP:
            src->set_adjacent(TOP, dst);
            dst->set_adjacent(DOWN, src);
            break;
        case RIGHT:
            src->set_adjacent(RIGHT, dst);
            dst->set_adjacent(LEFT, src);
            break;
        case DOWN:
            src->set_adjacent(DOWN, dst);
            dst->set_adjacent(TOP, src);
            break;
        case LEFT:
            src->set_adjacent(LEFT, dst);
            dst->set_adjacent(RIGHT, src);
    }
}

void procedural_generation::drunkards_walk_dfs() {
    const UI32 N = 50;
    const UI32 M = 200;
    const std::vector<I32> x_coords = { -1, 0, 1, 0 };
    const std::vector<I32> y_coords = { 0, 1, 0, -1 };
    std::vector<char> grid(N * M, ' ');

    auto e = [&N, &M] (I32 i, I32 j) { return i >= 0 && j >= 0 && i < N && j < M; };
    
    const UI32 required_empty_cells = 200;
    UI32 empty_cells = 0;

    std::stack<std::pair<I32, I32>> stk;
    const I32 start_x = r32ir(0, N - 1);
    const I32 start_y = r32ir(0, M - 1);
    stk.emplace(start_x, start_y);

    while (stk.size()) {
        auto [i, j] = stk.top(); stk.pop();
        if (empty_cells == required_empty_cells) continue;
        if (grid[i * M + j] != 'X') {
            grid[i * M + j] = 'X';
            empty_cells ++;
        }
        std::vector<std::pair<I32, I32>> valid_coords;
        for (I32 k = 0; k < 4; k++) {
            I32 I = i + x_coords[k];
            I32 J = j + y_coords[k];
            if (e(I, J))
                valid_coords.emplace_back(I, J);
        }
        I32 rdn_coord = r32ir(0, valid_coords.size() - 1);
        auto [I, J] = valid_coords[rdn_coord];
        stk.emplace(I, J);
    }

    std::cout << "empty cells: " << empty_cells << '\n';
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++)
            std::cout << grid[i * M + j];
        std::cout << '\n';
    }
}

void procedural_generation::drunkards_walk_bfs() {
    const UI32 N = 50;
    const UI32 M = 200;
    const std::vector<I32> x_coords = { -1, 0, 1, 0 };
    const std::vector<I32> y_coords = { 0, 1, 0, -1 };
    const UI32 required_empty_cells = 1000;
    const UI32 total_adjacents = 3;
    UI32 empty_cells = 0;
    std::vector<char> grid(N * M, ' ');

    auto e = [&N, &M, &grid] (I32 i, I32 j) { return i >= 0 && j >= 0 && i < N && j < M && grid[i * M + j] != 'X'; };

    std::queue<std::pair<I32, I32>> q;
    const I32 x_s = r32ir(0, N - 1);
    const I32 y_s = r32ir(0, M - 1);
    q.emplace(x_s, y_s);

    while (q.size()) {
        auto [i, j] = q.front(); q.pop();

        if (empty_cells == required_empty_cells) continue;
        
        std::vector<std::pair<I32, I32>> valid_coords;
        for (I32 k = 0; k < 4; k++) {
            I32 I = i + x_coords[k];
            I32 J = j + y_coords[k];
            if (e(I, J))
                valid_coords.emplace_back(I, J);
        }

        if (valid_coords.empty()) continue;

        UI32 adj = 0;
        while (empty_cells < required_empty_cells && valid_coords.size() && adj < total_adjacents) {
            I32 rdn_coord = r32ir(0, valid_coords.size() - 1);
            auto [I, J] = valid_coords[rdn_coord];
            grid[I * M + J] = 'X';
            q.emplace(I, J);
            valid_coords.erase(valid_coords.begin() + rdn_coord);
            empty_cells ++;
        }
    }
    
    std::cout << "empty cells: " << empty_cells << '\n';

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++)
            std::cout << grid[i * M + j];
        std::cout << '\n';
    }
}

void procedural_generation::create_room_path(std::shared_ptr<map_node> room) {
    const map room_map = room->get_map();
    const UI32 size = room_map.width() * room_map.height();
    std::vector<I32> weights(size);
    std::vector<I32> distance(size, 1e9);
    // defining random weights to all cells
    for (int i = 0; i < size; i++)
        weights[i] = r32ir(1, I32(1e9) >> 1);
    // find the shortest path
    std::priority_queue<std::tuple<I32, UI32, UI32>> pq;
}

std::shared_ptr<map_node> procedural_generation::generate_rooms(UI32 total_rooms) {
    std::vector<std::shared_ptr<map_node>> rooms;
    UI32 rooms_created = 0;
    while (rooms_created < total_rooms) {
        if (!rooms_created) {
            rooms.push_back(std::make_shared<map_node>(create_map_node()));
            rooms_created ++;
            continue;
        }
        
        I32 rdn_room_idx = r32ir(0, I32(rooms.size() - 1));
        node_dir rdn_connection_dir = map_node::rdn_node_dir();
        auto target_room = rooms[rdn_room_idx];
        
        if (target_room->get_adjacent(rdn_connection_dir) != nullptr)
            continue;
            
        auto new_room = std::make_shared<map_node>(create_map_node());
        connect_rooms(target_room, new_room, rdn_connection_dir);
        rooms.push_back(new_room);
        rooms_created ++;
    }
    // Pick a random room to be the root
    return rooms[r32ir(0, I32(rooms.size() - 1))];
}

map_node procedural_generation::create_map_node() {
    I32 width = r32ir(map::MAP_MIN_HEIGHT, map::MAP_MAX_HEIGHT);
    I32 height = r32ir(map::MAP_MIN_HEIGHT, width);
    return map_node(map(width, height));
}