add_rules("mode.debug", "mode.release")

add_requires("raylib")
add_requires("readerwriterqueue")

target("initLabAudioDemo")
    set_kind("binary")
    add_files("src/*.cpp")
    add_packages("raylib", "raygui", "readerwriterqueue")