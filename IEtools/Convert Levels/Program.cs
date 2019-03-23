using S3toIE2;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Convert_Levels {
    class Program {
        static void Main(string[] args) {
            S3toIE2Level.Init();

            goto SKIP;

            if (args.Length == 0)
                S3toIE2Level.ConvertTiledToIE2("Out (Tiled)/AIZ1/Scene.tmx");

            if (args.Length > 0 && args[0] == "SKIP")
                goto SKIP;

            if (args.Length > 0)
                S3toIE2Level.ConvertTiledToIE2(args[0]);
            return;

            SKIP:

            S3toIE2Level.ConvertLevel("AIZ", 1, "AIZ1", "Angel Island Zone Act 1", false);
            S3toIE2Level.ConvertLevel("AIZ", 2, "AIZ2", "Angel Island Zone Act 2", false);
            // S3toIE2Level.ConvertLevel("AIZ", 2, "AIZ2B", "Angel Island Zone Act 2 Boss", false); // Just needed 16x16 tiles.
            S3toIE2Level.ConvertLevel("HCZ", 1, "HCZ1", "Hydrocity Zone Act 1", false);
            S3toIE2Level.ConvertLevel("HCZ", 2, "HCZ2", "Hydrocity Zone Act 2", false);
            S3toIE2Level.ConvertLevel("MGZ", 1, "MGZ1", "Marble Garden Zone Act 1", false);
            S3toIE2Level.ConvertLevel("MGZ", 2, "MGZ2", "Marble Garden Zone Act 2", false);
            S3toIE2Level.ConvertLevel("CNZ", 1, "CNZ1", "Carnival Night Zone Act 1", false);
            S3toIE2Level.ConvertLevel("CNZ", 2, "CNZ2", "Carnival Night Zone Act 2", false);
            S3toIE2Level.ConvertLevel("ICZ", 1, "ICZ1", "Icecap Zone Act 1", false);
            S3toIE2Level.ConvertLevel("ICZ", 2, "ICZ2", "Icecap Zone Act 2", false);
            S3toIE2Level.ConvertLevel("LBZ", 1, "LBZ1", "Launch Base Zone Act 1", false);
            S3toIE2Level.ConvertLevel("LBZ", 2, "LBZ2", "Launch Base Zone Act 2", false);
            S3toIE2Level.ConvertLevel("MHZ", 1, "MHZ1", "Mushroom Hill Zone Act 1", true);
            S3toIE2Level.ConvertLevel("MHZ", 2, "MHZ2", "Mushroom Hill Zone Act 2", true);
            S3toIE2Level.ConvertLevel("FBZ", 1, "FBZ1", "Flying Battery Zone Act 1", true);
            S3toIE2Level.ConvertLevel("FBZ", 2, "FBZ2", "Flying Battery Zone Act 2", true);
            S3toIE2Level.ConvertLevel("SOZ", 1, "SOZ1", "Sandopolis Zone Act 1", true);
            S3toIE2Level.ConvertLevel("SOZ", 1, "SOZ1B", "Sandopolis Zone Act 1 Boss", true);
            S3toIE2Level.ConvertLevel("SOZ", 2, "SOZ2", "Sandopolis Zone Act 2", true);
            S3toIE2Level.ConvertLevel("LRZ", 1, "LRZ1", "Lava Reef Zone Act 1", true);
            S3toIE2Level.ConvertLevel("LRZ", 2, "LRZ2", "Lava Reef Zone Act 2", true);
            S3toIE2Level.ConvertLevel("LRZ", 2, "LRZ2B", "Lava Reef Zone Act 2 Boss", true);
            S3toIE2Level.ConvertLevel("HPZ", 1, "HPZ", "Hidden Palace Zone", true);
            S3toIE2Level.ConvertLevel("HPZ", 1, "HPZM", "Hidden Palace Zone Mini", true);
            S3toIE2Level.ConvertLevel("SSZ", 1, "SSZ1", "Sky Sanctuary Zone Act 1", true);
            S3toIE2Level.ConvertLevel("SSZ", 1, "SSZ1B", "Sky Sanctuary Zone Act 1 Boss", true);
            S3toIE2Level.ConvertLevel("SSZ", 2, "SSZ2", "Sky Sanctuary Zone Act 2", true);
            S3toIE2Level.ConvertLevel("DEZ", 1, "DEZ1", "Death Egg Zone Act 1", true);
            S3toIE2Level.ConvertLevel("DEZ", 2, "DEZ2", "Death Egg Zone Act 2", true);
            S3toIE2Level.ConvertLevel("DEZ", 2, "DEZ2B", "Death Egg Zone Act 2 Boss", true);
            S3toIE2Level.ConvertLevel("DDZ", 1, "DDZ", "The Doomsday Zone", true);
        }
    }
}
