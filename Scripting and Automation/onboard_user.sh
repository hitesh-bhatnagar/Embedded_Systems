#!/bin/bash

# Ask for username
read -p "Enter new username: " USERNAME

# Create a directory for the user
mkdir -p /tmp/$USERNAME

# Log onboarding message
echo "[$(date)] User $USERNAME onboarded" >> /tmp/user_onboard.log

echo "User $USERNAME setup complete! Directory: /tmp/$USERNAME"
