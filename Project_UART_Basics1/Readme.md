# Debugging with Live Expressions in STM32CubeIDE

This guide explains how to open and use the **Live Expressions** window in Debug Mode within STM32CubeIDE to monitor variable values in real-time during program execution.

## Table of Contents
- [Prerequisites](#prerequisites)
- [Step-by-Step Instructions](#step-by-step-instructions)
- [Tips](#tips)
- [Troubleshooting](#troubleshooting)

## Prerequisites
- STM32CubeIDE installed.
- A project configured and built in the IDE.
- A debug configuration set up for your target microcontroller (e.g., STM32).
- A debugger probe (e.g., ST-Link, J-Link) connected, if required by your setup.

## Step-by-Step Instructions
Follow these steps to open the Live Expressions window and monitor variables in Debug Mode:

1. **Build and Run Your Project**
   - Build your project normally by selecting **Project → Build Project** or clicking the build icon (🔨).
   - Run the project in normal mode to ensure it compiles and executes without errors.

2. **Start the Debugger**
   - Click the **bug icon (🪲)** in the toolbar or select **Run → Debug** to start the debugger.
   - The IDE will switch to the Debug Perspective, and the program will pause at the first breakpoint (if set).

3. **Open the Live Expressions Window**
   - If the Live Expressions window is not visible, go to **Window → Show View → Live Expressions**.
   - The Live Expressions tab should appear in the Debug Perspective, typically alongside other views like Variables and Breakpoints.

4. **Add an Expression**
   - In the Live Expressions window, click **Add Expression** (or the ➕ icon).
   - Type the name of the variable you want to monitor (e.g., `message`) and press Enter.

5. **Monitor Live Data**
   - Expand the added expression in the Live Expressions window to view its value.
   - Resume program execution (e.g., click the Resume button or press **F8**) to see real-time updates to the variable’s value as the program runs.

## Tips
- **Resume After Breakpoints**: Ensure the program is running (not paused at a breakpoint) to see live updates in the Live Expressions window. Use the **Resume** button (▶️) to continue execution.
- **Enable Live Expressions**: For STM32CubeIDE, ensure the Live Expressions mechanism is enabled in the debug configuration. Go to **Run → Debug Configurations → Debugger tab** and check the **Enable Live Expressions** option.
- **Variable Scope**: Only global variables or variables in the current scope are available for monitoring in Live Expressions.
- **Performance**: Adding too many expressions may slow down debugging, especially on resource-constrained microcontrollers.

## Troubleshooting
- **Live Expressions Not Updating**: Verify that the program is running and not paused. Ensure the **Enable Live Expressions** option is checked in the debug configuration.
- **Variable Not Found**: Check that the variable is in scope and correctly spelled. Local variables may not be accessible outside their function.
- **J-Link Issues**: If using a J-Link debugger, some versions may not fully support Live Expressions. Consider using an ST-Link or check with the debugger vendor for updates.
- **Window Not Visible**: If the Live Expressions view does not appear, reset the Debug Perspective by going to **Window → Perspective → Reset Perspective**.