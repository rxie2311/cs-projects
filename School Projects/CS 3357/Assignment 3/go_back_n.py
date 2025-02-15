# Author: Raymond Xie
# Student No: 251275727
# Description: A program that simulates the Go-Back-N protocol.

import threading
import logging
import queue
import time


class GBN_sender:
    # Constructor method
    def __init__(self, input_file, window_size, packet_len, nth_packet, send_queue, ack_queue, timeout_interval,
                 logger):
        # Instance variables
        self.input_file = input_file
        self.window_size = window_size
        self.packet_len = packet_len
        self.nth_packet = nth_packet
        self.send_queue = send_queue
        self.ack_queue = ack_queue
        self.timeout_interval = timeout_interval
        self.logger = logger
        # Base is initialized as 0
        self.base = 0
        # Packets list is created by calling on prepare_packets method
        self.packets = self.prepare_packets()
        # List variables
        self.acks_list = [False] * len(self.packets)
        self.packet_timers = [0] * len(self.packets)
        self.dropped_list = []

        # ADDED EXTRA VARIABLES FOR METHOD USE
        # Extra variable to keep track of the number of packets until one needs to be dropped
        self.drop = 0
        # Extra variable used to keep track of the last sent packet number
        self.sent_packs = []
        # Extra variable to keep track of the most recently dropped packet
        self.dropped_packs = []

    # Method that prepares the packets by adding them to a list and returning the list
    def prepare_packets(self):
        # Program tries to read from the file
        try:
            # Reading from the input file
            f = open(self.input_file, "r")
            # String to store the entire message in the file in binary
            binary_string = ""
            # Uses a nested loop to loop through each line in f, and each character in each line and convert to binary
            for line in f:
                for char in line:
                    # Adds the character converted to binary to the string variable
                    binary_string = binary_string + format(ord(char), "08b")

            # List to store all the packets
            pack_list = []
            # Packet length - 16 = Number of bits per packet
            num_bits = self.packet_len - 16
            # Temp variable to store each character in the binary string
            temp = ""
            # Helps keep track of how many bits have been added to the temp string so far
            counter = 0
            # Helps keep track of the current packet number, will be formatted into a 16-bit sequence number
            seq_counter = 0
            # Loops through the entire binary string
            for n in range(len(binary_string)):
                # If n is currently on the last index of the string
                if n == len(binary_string) - 1:
                    # Adds the last bit to the packet and the 16-bit sequence number
                    temp = temp + binary_string[n] + format(seq_counter, "016b")
                    # Adds the packet to the packet list
                    pack_list.append(temp)
                    # Resets temp
                    temp = ""
                    # Breaks out of the loop
                    break

                # If the number of bits saved so far is the max size for the packet
                if counter == num_bits:
                    # Adds the bits to the packet along with the 16-bit sequence number
                    temp = temp + format(seq_counter, "016b")
                    # Adds the packet to the packet list
                    pack_list.append(temp)
                    # Resets temp
                    temp = ""
                    # Increments the sequence counter
                    seq_counter += 1
                    # Reset the temp string counter
                    counter = 0

                # Adding the current bit to temp
                temp = temp + binary_string[n]
                # Incrementing the counters
                counter += 1

            # Returns the list at the end
            return pack_list
        # If the file is not found, then sends an error message
        except FileNotFoundError:
            print(f"Error: The file {self.input_file} was not found.")

    # Method that sends all packets within the sliding window starting from the base index
    def send_packets(self):
        # Checking if base added to the sliding window is smaller than the length of the packet list
        if self.base + self.window_size < len(self.packets):
            # If smaller, then use base + window size as the stopping index for the loop
            stop_index = self.base + self.window_size
        # If not smaller, then use the length of packets as the stopping index instead
        else:
            stop_index = len(self.packets)

        # Using a for loop to iterate through the packets inside the sliding window
        for n in range(self.base, stop_index):
            # Only sends the packet if the packet sequence number index in the acks list is False
            if not self.acks_list[n]:
                # Saves the packet into a temp variable and logs it
                pack = self.packets[n]
                self.logger.info(f"sending packet {n}")
                # Adds 1 to the drop counter
                self.drop += 1

                # Checking if the drop counter is equal to the nth packet and that it has not been dropped yet
                if self.drop == self.nth_packet and n not in self.dropped_packs:
                    # Adds the packet sequence number to the dropped list
                    self.dropped_list.append(n)
                    # Adds the packet sequence number to the dropped_packs list as the most recently dropped packet
                    self.dropped_packs.append(n)
                    # Logs the dropped packet
                    self.logger.info(f"packet {n} dropped")
                    # Sets the drop counter back down to 0
                    self.drop = 0
                    # Saves the current time when this line of code is ran into the packet timers list
                    self.packet_timers[n] = time.time()
                # If the packet does not need to be dropped
                else:
                    # Puts the packet in the send queue
                    self.send_queue.put(pack)
                    # Saves the packet number into the sent packets list
                    self.sent_packs.append(n)
                    # Saves the current time when this line of code is ran into the packet timers list
                    self.packet_timers[n] = time.time()

    # Method to send the last packet in the sliding window
    def send_next_packet(self):
        # Increasing the base by 1
        self.base += 1
        # Index number of the last packet in the sliding window
        index_last = self.base + self.window_size

        # If the index of the last packet is smaller than the length of the packet list
        if index_last < len(self.packets):
            # Saves the packet into a temp variable
            # (the index being the last index - 1 due to list indexing starting at 0)
            pack = self.packets[index_last - 1]
            self.logger.info(f"sending packet {index_last - 1}")
            # Adds 1 to the drop counter
            self.drop += 1

            # Checking if the last index is the nth packet and that it has not been dropped yet
            if self.drop == self.nth_packet and index_last - 1 not in self.dropped_packs:
                # Adds the packet sequence number to the dropped list
                self.dropped_list.append(index_last - 1)
                # Adds the packet sequence number to the dropped_packs list as the most recently dropped packet
                self.dropped_packs.append(index_last - 1)
                # Logs the dropped packet
                self.logger.info(f"packet {index_last - 1} dropped")
                # Sets the drop counter back down to 0
                self.drop = 0
                # Saves the current time when this line of code is ran into the packet timers list
                self.packet_timers[index_last - 1] = time.time()
            # If the packet does not need to be dropped
            else:
                # Puts the packet in the send queue
                self.send_queue.put(pack)
                # Saves the packet number into the sent_packs list
                self.sent_packs.append(index_last - 1)
                # Saves the current time when this line of code is ran into the packet timers list
                self.packet_timers[index_last - 1] = time.time()

        # If the base added to the window size is bigger than the packet list length,
        # then default packet list length as the last packet in the sliding window
        elif self.base + self.window_size >= len(self.packets):
            # Saves the packet into a temp variable
            pack = self.packets[len(self.packets) - 1]
            self.logger.info(f"sending packet {len(self.packets) - 1}")
            # Adds 1 to the drop counter
            self.drop += 1

            # Checking if the last index is the nth packet and that it has not been dropped yet
            if self.drop == self.nth_packet and len(self.packets) - 1 not in self.dropped_packs:
                # Adds the packet sequence number to the dropped list
                self.dropped_list.append(len(self.packets) - 1)
                # Adds the packet sequence number to the dropped_packs list as the most recently dropped packet
                self.dropped_packs.append(len(self.packets) - 1)
                # Logs the dropped packet
                self.logger.info(f"packet {len(self.packets) - 1} dropped")
                # Sets the drop counter back down to 0
                self.drop = 0
                # Saves the current time when this line of code is ran into the packet timers list
                self.packet_timers[len(self.packets) - 1] = time.time()
            # If the packet does not need to be dropped
            else:
                # Puts the packet in the send queue
                self.send_queue.put(pack)
                # Saves the packet number into the sent packets list
                self.sent_packs.append(len(self.packets) - 1)
                # Saves the current time when this line of code is ran into the packet timers list
                self.packet_timers[len(self.packets) - 1] = time.time()

    # Method that checks for timeouts
    def check_timers(self):
        # Checking if base added to the sliding window is smaller than the length of the packet list
        if self.base + self.window_size < len(self.packets):
            # If smaller, then use base + window size as the stopping index for the loop
            stop_index = self.base + self.window_size
        # If not smaller, then use the length of packets as the stopping index instead
        else:
            stop_index = len(self.packets)

        # For loop to cycle through the timers for the sequence numbers in the packet window
        for n in range(self.base, stop_index):
            # Checks if sequence number n is in the dropped packets list
            if n in self.dropped_packs:
                # The current time when this line of code is run
                curr_time = time.time()
                # Checks if the time elapsed between when the packet was sent and the current time is greater than the
                # timeout interval
                if int(round(curr_time - self.packet_timers[n])) >= self.timeout_interval:
                    # Removes the packet from the dropped list since it is being resent
                    self.dropped_packs.remove(n)
                    # Logs the timeout message
                    self.logger.info(f"packet {n} timed out")
                    # Returns True since the packet timed out
                    return True

        # If there were no timeouts, returns False
        return False

    # Method that continuously listens for acknowledgements from the receiver
    def receive_acks(self):
        while True:
            try:
                # Gets the ack from the ack queue with a timeout of 1 second
                ack = self.ack_queue.get(timeout=1)

                # If the ack received has not been marked as True in the ack_list yet
                if not self.acks_list[ack]:
                    # Sets the ack to True in the list
                    self.acks_list[ack] = True
                    # Logs info about receiving the ack
                    self.logger.info(f"ack {ack} received")
                    # If statement to prevent the method from sending the last packet multiple times when
                    # receiving an ack
                    if self.sent_packs[-1] != len(self.packets)-1:
                        self.send_next_packet()
                    # If the last ack needed is marked True, then the method will end
                    elif self.acks_list[len(self.packets)-1]:
                        break

                else:
                    self.logger.info(f"ack {ack} received, Ignoring")

            # Breaks out of the method if the acknowledgement queue is empty after a 1 second delay
            except queue.Empty:
                break

    # Method that runs the sender class
    def run(self):
        # Sending out the initial packets
        self.send_packets()

        # While loop that will loop until the base reaches the packet list length
        while self.base < len(self.packets):
            # Starts a thread to listen for acknowledgements
            threading.Thread(target=self.receive_acks()).start()
            # If a timeout occurs (check_timers returned True), then resend all packets in the window using send_packets
            if self.check_timers():
                self.send_packets()
            # If the last ack needed is True, then breaks out of the loop as well
            elif self.acks_list[len(self.packets)-1]:
                break

        # Sends None into the queue once all packets have been sent and acknowledged
        self.send_queue.put(None)


class GBN_receiver:
    # Constructor method
    def __init__(self, output_file, send_queue, ack_queue, logger):
        # Instance variables
        self.output_file = output_file
        self.send_queue = send_queue
        self.ack_queue = ack_queue
        self.logger = logger
        # Expected sequence number initialized at 0
        self.expected_seq_num = 0
        # List variables
        self.packet_list = []

    # Method that helps process the packet sent by the sender
    def process_packet(self, packet):
        # Removing the binary sequence number at the last 16 digits of the packet
        seq_num = packet[-16:]
        # Saving only the packet data to a temp variable
        pack_data = packet[:-16]
        # Converting the sequence number back into an int
        int_seq_num = int(seq_num, 2)

        # Checking if the sequence number matches the expected sequence number
        if int_seq_num == self.expected_seq_num:
            # Adds the packet data only into the packet list
            self.packet_list.append(pack_data)
            # Sends ack to sender
            self.ack_queue.put(int_seq_num)
            # Logs info that the packet has been received
            self.logger.info(f"packet {int_seq_num} received")
            # Increases the expected sequence number by 1
            self.expected_seq_num += 1
            # Returns true
            return True
        # If the sequence number does not match the expected sequence number
        else:
            # Sends the last ack to sender
            self.ack_queue.put(self.expected_seq_num - 1)
            # Logs info that the packet has been received
            self.logger.info(f"packet {int_seq_num} received out of order")
            # Returns false
            return False

    # Method that writes all the packets to a file at the end
    def write_to_file(self):
        # Adding all packet list data into a singular binary string
        binary_string = "".join(self.packet_list)
        # Temp variable to store the decoded binary
        message = ""
        # For loop to decode the binary back into characters
        for n in range(0, len(binary_string), 8):
            # Decodes every 8 bits into a character (since the character was padded to 8 bits)
            decoded_char = chr(int(binary_string[n:n + 8], 2))
            # Concatenates into the temp variable
            message = message + decoded_char

        # Writing the decoded message into the output file
        f = open(self.output_file, "w")
        f.write(message)
        # Closes the file after writing to it
        f.close()

    # Method to run the receiver class
    def run(self):
        # Continuous loop to listen for packets in the send queue
        while True:
            try:
                # Taking the packet from the send queue with a 1 second timeout
                pack = self.send_queue.get(timeout=1)

                # If None is received from the send queue
                if pack is None:
                    # Breaks out of the loop
                    break

                # If the packet is not None, then calls on process_packet to process the packet
                self.process_packet(pack)

            # If the send queue is empty for 1 second, then it will restart the loop to avoid a blocking call
            except queue.Empty:
                continue

        # Writes to the file at the end of the program
        self.write_to_file()