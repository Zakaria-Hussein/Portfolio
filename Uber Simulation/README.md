# CSCI 3081 Project - Drone Simulation System

Team number: Team-010-34

Team member’s names, and x500: Abdirahman Mohamed (moha0950), Abdirabi Mohamed (moha1184), Zakaria Hussein (Husse285), Bilal Osman (OSMAN353). 

This project is about creating different entities that utilize search algorithms for paths of travel. Here are the steps to run the simulation

Run the first three commands in terminal:

1. make clean

2. make -j

3. ./build/bin/transit_service 8081 apps/transit_service/web/

4. Navigate to http://127.0.0.1:8081 and you should see a visualization.

5. Navigate to http://127.0.0.1:8081/schedule.html and you should see a page to schedule the trips.

This project simulates a drone’s ability to pick a robot and drop it off at its requested destination while using the search algorithm chosen by the user. 

In this new feature, we used the factory design pattern to add recharge stations for the drone. We also added a battery to the drone and employed the decorator design pattern to wrap the battery around the drone. Furthermore, we utilized the observer design pattern to change the color of the battery as the simulation progressed, providing the user with a visual indication of the battery's charge level. 

We added a new feature to the drone where it contains a battery that has constantly draining charge. Once the charge gets low enough, it goes to a nearby charging station. This new feature is non-intractable because we are simulating a battery. 

This project was interesting because it allowed for the drone situation to be more “realistic” and “dynamic”. When we look back retrospectively, we could make improvements to our sprints by having more “set in stone” timeframes to complete tasks.

Video Presentation Link: https://umn.zoom.us/rec/play/jewW2FRZyv0rpXKK1Pxw234h4AG7bvo9_nlhXYdUO1bbaFndkoD_ZBIEHxqm72TZ13WHcQtx-r2B2C4d.S-MEMgbX5BQVQu1W?continueMode=true 
