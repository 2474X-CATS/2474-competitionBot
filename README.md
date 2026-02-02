<h1>2474X-CATS CompetitionBot — 2025–26 Push Back Season</h1>

<h2>Author(s): <br/>
    <ul>
    <li>Jackson Scott (Primary Developer)</li> 
    <li>Samiksha Menaka </li>
    <li>Saanvi Akula </li> 
    </ul>
</h2>
<h2>Game: VEX Robotics Competition – Push Back</h2>
<h2>Robot: Competition-ready V5 robot with modular architecture, command-based control, and advanced motion planning.</h3>

<h3>🚀 Overview</h3>

This repository contains the control software for Team 2474X-CATS’ 2025–26 VEX Push Back robot. The system is designed for robust autonomous routines, precise driver control, and modular subsystems, making it easy to scale, debug, and iterate during competition.

<h4>Key Features:</h4>
<ul>
<li><b>Command–Subsystem Architecture</b> — separates hardware, behavior, and control logic.</li>
<li><b>Centralized Command Manager</b> — organizes and schedules robot actions.</li>
<li><b>Subsystem Abstraction</b> — drivebase, intake, indexer, matchloader, hooks.</li>
<li><b>Advanced Control Layer</b> — feedforward, PID, and trajectory controllers for precise motion.</li>
<li><b>Telemetry Layer</b> — centralized diagnostics and sensor reporting.</li>
<li><b>Utilities</b> — helpers like Location for field positioning.</li>
</ul>

<h3>📁 File Structure</h3> <br/>
src/ <br/>
├── main.cpp<br/>
├── commands.cpp / commands.h  [# Command manager and registry] <br/>
├── architecture/<br/>
│   ├── command.cpp / command.h  [# Base command interface] <br/>
│   ├── subsystem.cpp / subsystem.h  [# Base subsystem interface] <br/>
│   ├── robot.cpp / robot.h  [# Central robot controller] <br/>
│   ├── telemetry.cpp / telemetry.h  [# Telemetry and diagnostics] <br/>
├── utilities/ <br/>
│   └── location.cpp / location.h  [# Robot field position helper] <br/>
├── subsystems/ <br/> 
│   ├── drivebase.cpp / drivebase.h <br/>
│   ├── intake.cpp / intake.h <br/>
│   ├── indexer.cpp / indexer.h <br/>
│   ├── matchloader.cpp / matchloader.h <br/>
│   └── hooks.cpp / hooks.h <br/>
└── control/ <br/>
    ├── feedforward.cpp / feedforward.h <br/>
    ├── pidcontroller.cpp / pidcontroller.h <br/>
    └── trajectorycontroller.cpp / trajectorycontroller.h <br/>

<h3>🏗 Architecture Overview</h3>

The software is built with modularity, reusability, and clarity in mind.

<h4>Core Concepts:</h4> 
<ul>
  <li><b>Subsystems</b> — Encapsulate hardware and low-level control for each robot mechanism.</li>
  <li><b>Commands</b> — Represent discrete robot actions; scheduled by the Robot controller.</li>
  <li><b>Robot</b> — Orchestrates subsystems and commands; handles competition states.</li>
  <li><b>Control Layer</b> — Handles motion control using PID, feedforward, and trajectory tracking.</li>
  <li><b>Telemetry</b> — Provides diagnostics and sensor feedback.</li>
  <li><b>Utilities</b> — Provide helper functions like robot positioning.</li>
</ul>

<h3>Subsystems</h3>

| Subsystem	 | Purpose                             |
| :---:      | :---:                               |
| Drivebase	 | Robot drivetrain control            |
| Intake	 | Acquire game objects                |
| Indexer	 | Move blocks internally for scoring  |
| Matchloader| Feed blocks into scoring position   |
| Hooks	     | Endgame hooks for field interaction | 


<h3>Commands</h3>
Encapsulates high-level robot behaviors such as: 
</br>

<ul>
<li>Driving to a location using various path types [EUCLIDEAN, MANHATTAN_XY, MANHATTAN_YX]</li>
<li>Intake Cubes</li>
<li>Score blocks on a certain goal</li> 
<li>Deploy the Matchloader</li>
<li>Deploy hooks</li>
</ul> 

<h3>Control Layer</h3>
<ul>
  <li><b>Feedforward</b> — Predicts required motor output based on desired speed/acceleration.</li> 
  <li><b>Trapezoidal Motion Profile</b> — Outputs requires drivbase velocities to reach a certai distance given time elapsed</li>
  <li><b>PID Controller</b> — Feedback loop to correct errors in motion.</li>
  <li><b>Trajectory Controller</b> - Combines Feedfoward control with a corrective PID Controller to follow a Trapezoidal Motion profile path with correction</li> 
</ul>

The robot uses a command–subsystem architecture with a centralized command manager and telemetry. Subsystems handle hardware, commands define actions, and the control layer ensures precise autonomous and driver performance.
