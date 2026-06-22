player = {
    name = "Player1",
    x = 1,
    y = 1
}

inventory = {
    {id = 1, name = "Dirt", amount = 10},
    {id = 2, name = "Seed", amount = 5},
    {id = 3, name = "Wood", amount = 2}
}

world = {
    {1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 2, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1}
}

function showPosition()
    print("Nama Player: " .. player.name)
    print("Posisi X: " .. player.x)
    print("Posisi Y: " .. player.y)
end

function moveTo(targetX, targetY)
    player.x = targetX
    player.y = targetY

    print("Player pindah ke X: " .. player.x .. ", Y: " .. player.y)
end

function showInventory()
    print("=== INVENTORY ===")

    for i, item in ipairs(inventory) do
        print(i .. ". " .. item.name .. " | ID: " .. item.id .. " | Jumlah: " .. item.amount)
    end
end

function checkAmount(itemId)
    for i, item in ipairs(inventory) do
        if item.id == itemId then
            return item.amount
        end
    end

    return 0
end

function showWorld()
    print("=== WORLD MAP ===")

    for y = 1, #world do
        local row = ""

        for x = 1, #world[y] do
            row = row .. world[y][x] .. " "
        end

        print(row)
    end
end

function checkTile(x, y)
    if world[y] == nil then
        return nil
    end

    if world[y][x] == nil then
        return nil
    end

    return world[y][x]
end

function hitTile(x, y)
    local tile = checkTile(x, y)

    if tile == nil then
        print("Koordinat tidak valid.")
        return
    end

    if tile == 0 then
        print("Tile kosong, tidak ada yang dipukul.")
    elseif tile == 1 then
        print("Kamu memukul Dirt.")
        world[y][x] = 0
    elseif tile == 2 then
        print("Kamu memukul Tree.")
        world[y][x] = 0
    end
end

function addItem(itemId, amount)
    for i, item in ipairs(inventory) do
        if item.id == itemId then
            item.amount = item.amount + amount
            return
        end
    end

    table.insert(inventory, {id = itemId, name = "Item" .. itemId, amount = amount})
end

while true do
    print("")
    print("=== MINI FARM WORLD ===")
    print("1. Lihat posisi player")
    print("2. Jalan ke koordinat")
    print("3. Lihat inventory")
    print("4. Cek jumlah item")
    print("5. Lihat map")
    print("6. Pukul tile")
    print("7. Keluar")
    io.write("Pilih menu: ")

    local pilihan = tonumber(io.read())

    if pilihan == 1 then
        showPosition()

    elseif pilihan == 2 then
        io.write("Masukkan X: ")
        local x = tonumber(io.read())

        io.write("Masukkan Y: ")
        local y = tonumber(io.read())

        moveTo(x, y)

    elseif pilihan == 3 then
        showInventory()

    elseif pilihan == 4 then
        io.write("Masukkan item ID: ")
        local id = tonumber(io.read())

        local amount = checkAmount(id)
        print("Jumlah item ID " .. id .. ": " .. amount)

    elseif pilihan == 5 then
        showWorld()

    elseif pilihan == 6 then
        io.write("Masukkan X tile: ")
        local x = tonumber(io.read())

        io.write("Masukkan Y tile: ")
        local y = tonumber(io.read())

        hitTile(x, y)

    elseif pilihan == 7 then
        print("Program selesai.")
        break

    else
        print("Pilihan tidak valid.")
    end
end