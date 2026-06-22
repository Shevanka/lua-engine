-- Panggil fungsi dari C via tabel Engine
Engine.log("Halo dari Lua script!")

local waktu = Engine.getTime()
Engine.log("Unix timestamp sekarang: " .. waktu)

local hasil = Engine.add(10, 32)
Engine.log("Hasil 10 + 32 = " .. hasil)

-- Baca file dari C
local isi = Engine.readFile("README.md")
if isi then
    Engine.log("Isi file berhasil dibaca.")
else
    Engine.log("File tidak ditemukan.")
end

-- Lua standard library tetap bisa dipakai
print("Ini print bawaan Lua: " .. math.sqrt(144))