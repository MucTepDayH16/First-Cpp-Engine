import qbs

Project {
    minimumQbsVersion: "1.7.1"

    CppApplication {
        consoleApplication: true
        files: [
            "../Project/Main.cpp",
            "entity.cpp",
            "entity.h",
            "execute.cpp",
            "execute.h",
            "graphic.cpp",
            "graphic.h",
            "input.cpp",
            "input.h",
            "input_listener.cpp",
            "main.cpp",
            "mainheader.h",
            "state.cpp",
            "state.h",
        ]

        Group {     // Properties for the produced executable
            fileTagsFilter: "application"
            qbs.install: true
        }
    }
}
