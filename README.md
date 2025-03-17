# AstroRev

🚀 **AstroRev** is an intergalactic racing game where you pilot futuristic vehicles through space in split-screen mode, featuring innovative racing mechanics like hover physics, boosts, and reduced gravity zones. Sharpen your piloting skills across dynamic and competitive environments. Built with **Unreal Engine** using **C++** and **Blueprints**, AstroRev immerses you in an epic racing experience through the universe! 🌌🏎️✨

## 🎮 Features
- **Intense Space Racing** – Race through intergalactic tracks, facing off against opponents in high-speed races.
- **Hover Physics Simulation** – Experience reduced gravity and normal gravity effects as you adapt your hovercraft to each terrain's conditions.
- **Boosts and Gravity Zones** – Use boosts to accelerate and navigate through zones with reduced gravity to gain an edge!
- **Vehicle Customization** – Upgrade your hovercraft's capabilities between races to enhance speed, control, and efficiency.
- **Dynamic Environments** – Tracks with different gravity effects, obstacles, and boosts scattered throughout the levels.

## 🛠️ Development Details
- Built with **Unreal Engine**.
- Main gameplay coded in **C++**.
- User interface developed using **Blueprints**.
- **Modular Codebase** – Vehicles inherit from `BaseCar`, allowing flexibility for adding new vehicles and behaviors.
  – PowerUps inherit from `BasePowerUp`.

### 📂 Important Files
- **Main Vehicle Class:** [BaseCar](Source/AstroRev/Public/Pawns/BaseCar.h)
- **Main PowerUp Class:** [BasePowerUp](Source/AstroRev/Public/PowerUp/BasePowerUp.h)
- **Boost PowerUp System:** [BoosterPowerUp](Source/AstroRev/Public/PowerUp/BoosterPowerUp.h)
- **Reduced Gravity Simulation:** [ZeroGravityPowerUp](Source/AstroRev/Public/PowerUp/ZeroGravityPowerUp.h)
- **Engine System:** [HovercraftMovementComponents](Source/AstroRev/Public/Components)

## 🚀 Adding Content
AstroRev is designed for easy expansion:
- **Adding New Levels:** Extend the level list and configure gravity zones, obstacles, and PowerUps for each track.
- **Creating New Vehicles:** Inherit from `BaseCar`, define unique behaviors for your hovercraft, and integrate them into the game.
- **Using the PowerUp System:** Add new types of PowerUps or objects by inheriting from `BasePowerUp`.

## 👥 Contributeurs
- [@Zhailendra](https://github.com/Zhailendra)
- [@BySkullZ](https://github.com/BySkullZ)
- [@46Yuu](https://github.com/46Yuu)
