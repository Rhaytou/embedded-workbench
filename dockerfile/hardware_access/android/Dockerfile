FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive
ENV ANDROID_HOME=/opt/android-sdk
ENV ANDROID_SDK_ROOT=/opt/android-sdk

# Install required tools
RUN apt-get update && apt-get install -y \
    wget unzip curl git openjdk-17-jdk \
    && rm -rf /var/lib/apt/lists/*

RUN apt-get update && apt-get install -y zip \
    && rm -rf /var/lib/apt/lists/*

# Create android SDK directory
RUN mkdir -p $ANDROID_HOME/cmdline-tools

# Download Android command-line tools
RUN wget https://dl.google.com/android/repository/commandlinetools-linux-11076708_latest.zip -O /tmp/cmdline.zip \
    && unzip /tmp/cmdline.zip -d $ANDROID_HOME/cmdline-tools \
    && mv $ANDROID_HOME/cmdline-tools/cmdline-tools $ANDROID_HOME/cmdline-tools/latest

# Add tools to PATH
ENV PATH="$ANDROID_HOME/cmdline-tools/latest/bin:$ANDROID_HOME/platform-tools:$ANDROID_HOME/emulator:$PATH"

# Add Android build-tools (d8) to PATH
ENV PATH="$ANDROID_HOME/cmdline-tools/latest/bin:$ANDROID_HOME/platform-tools:$ANDROID_HOME/emulator:$ANDROID_HOME/build-tools/34.0.0:$PATH"

# Install SDK components
RUN yes | sdkmanager --licenses
RUN sdkmanager "platform-tools" \
               "build-tools;34.0.0" \
               "platforms;android-34" \
               "ndk;26.3.11579264"

# Expose ADB port for debugging
EXPOSE 5555

WORKDIR /workspace

















































































