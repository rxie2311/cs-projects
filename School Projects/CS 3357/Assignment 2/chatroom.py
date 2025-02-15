# Author: Raymond Xie
# Student No: 251275727
# Description: A chatroom that has both a TCP and UDP server and client.

import socket
import sys
import select
import threading


# TCP Server Class
class ServerTCP:
    # Constructor method
    def __init__(self, server_port):
        # Instance variables
        self.server_port = server_port
        self.local_addr = socket.gethostbyname(socket.gethostname())
        self.clients = {}

        # Threading Events
        self.run_event = threading.Event()
        self.handle_event = threading.Event()

        # Setting up TCP server
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        # Binding to local address and server port
        self.server_socket.bind((self.local_addr, self.server_port))

    # Method that helps with accepting new client connections
    def accept_client(self):
        try:
            # Will loop as long as the run event is not set
            while not self.run_event.is_set():
                # Using select to ensure there is an incoming connection before calling accept()
                readable, writeable, exceptional = select.select([self.server_socket], [], [], 1)
                if readable:
                    # Accepts the incoming socket
                    conn, client_addr = self.server_socket.accept()
                    # Decodes the name sent from the client
                    name = conn.recv(4096).decode("utf-8")

                    # Cycles through the values in the client dictionary to see if the name entered is unique
                    for i in self.clients.values():
                        # If the name is a duplicate name of an already joined client
                        if i == name:
                            # Sends "Name already taken" to the client and returns false
                            response = "Name already taken"
                            conn.sendall(response.encode("utf-8"))
                            return False

                    # Adding user's unique name as value and client socket as the key into client dictionary
                    self.clients[conn] = name
                    # Sending "Welcome" to the client
                    response = "Welcome"
                    conn.sendall(response.encode("utf-8"))
                    # Broadcasting a message to the server chat
                    sys.stdout.write(f"\nUser {name} joined")
                    sys.stdout.flush()
                    # Uses threading to handle multiple clients
                    threading.Thread(target=self.handle_request, args=(conn, client_addr)).start()
                    # Returns True
                    return True

        # Catches all exceptions and stops the server if an exception occurs
        except Exception as e:
            print(f"\nException: An exception ({e}) occurred while accepting the client.")
            self.shutdown()

    # Extra method added to help with threading
    def handle_request(self, conn, client_addr):
        try:
            # Calls on handle request to handle the request from conn
            self.handle_client(conn)

        # Catches all exceptions and stops the server if an exception occurs
        except Exception as e:
            print(f"\nException: An exception ({e}) occurred while handling the client.")
            conn.close()

    # Method that helps close the connection for a given client socket and removing the socket from the dictionary
    def close_client(self, client_socket):
        try:
            # Removing the client socket from the dictionary using it as a key
            self.clients.pop(client_socket)
            # Closes the client socket and returns True
            client_socket.close()
            return True

        # Returns False if the key was not found
        except KeyError:
            return False

    # Method that helps broadcast messages to the terminal and to connected clients
    def broadcast(self, client_socket_sent, message):
        # Getting the name of the client from the client dictionary using client socket sent as a key
        x = self.clients.get(client_socket_sent)

        # Broadcasting a message to the terminal based on what the message contains
        if message.lower() == "join":
            sys.stdout.write(f"\nUser {x} joined")
            sys.stdout.flush()
        elif message.lower() == "exit":
            sys.stdout.write(f"\nUser {x} left")
            sys.stdout.flush()
        else:
            sys.stdout.write(f"\n{x}: {message}")
            sys.stdout.flush()

        # Sending the message to all clients connected except for the client socket sent
        for i in self.clients:
            if i != client_socket_sent:
                if message == "join":
                    response = f"\nUser {x} joined"
                    i.sendall(response.encode("utf-8"))
                elif message == "exit":
                    response = f"\nUser {x} left"
                    i.sendall(response.encode("utf-8"))
                else:
                    response = f"\n{x}: {message}"
                    i.sendall(response.encode("utf-8"))

    # Method that helps shut down the server by closing all sockets
    def shutdown(self):
        # Sending the message to all clients connected
        for i in self.clients:
            response = "server-shutdown"
            i.sendall(response.encode("utf-8"))

        # Setting both threading events
        self.handle_event.set()
        self.run_event.set()

        # Closing server socket
        self.server_socket.close()

    # Method that returns the number of connected clients (number of items in the dictionary)
    def get_clients_number(self):
        # Getting the length of the dictionary
        client_no = len(self.clients)
        # Returning the length of the dictionary
        return client_no

    # Method that listens to the client until the handle event is set, will break the loop when "exit" is received
    def handle_client(self, client_socket):
        try:
            # Using select to detect if there is an incoming message from the client socket before calling recv()
            while not self.handle_event.is_set():
                readable, writeable, exceptional = select.select([client_socket], [], [], 1)
                if readable:
                    # Decodes the client request
                    response = client_socket.recv(4096).decode("utf-8")
                    # Calls on broadcast method
                    self.broadcast(client_socket, response)
                    # If the message received is "exit"
                    if response.lower() == "exit":
                        # Terminates the client socket and breaks out of the loop
                        self.close_client(client_socket)
                        break

        # Catches all exceptions and calls close_client if an error occurs
        except Exception as e:
            print(f"Exception: An exception ({e}) occurred while handling the client")
            self.close_client(client_socket)

    # Method that runs the server
    def run(self):
        # Starts the server
        self.server_socket.listen(5)

        # Will loop as long as run_event is not set
        while not self.run_event.is_set():
            try:
                # Calls on accept_client to start accepting clients
                self.accept_client()

            # Catches KeyboardInterrupt Exception and shuts down the server if detected
            except KeyboardInterrupt:
                self.handle_event.set()
                self.shutdown()
                self.run_event.set()


# TCP Client Class
class ClientTCP:
    # Constructor method
    def __init__(self, client_name, server_port):
        # Setting up the server
        self.server_addr = socket.gethostbyname(socket.gethostname())
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        # Instance variables
        self.server_port = server_port
        self.client_name = client_name

        # Setting up Threading Events
        self.exit_run = threading.Event()
        self.exit_receive = threading.Event()

    # Method to help the client connect to the server
    def connect_server(self):
        # Sending a connection request to the server
        self.client_socket.connect((self.server_addr, self.server_port))
        # Sending the client's name to the server as a message
        name = self.client_name
        self.client_socket.sendall(name.encode("utf-8"))

        # Using select to detect if the server has a response before calling recv()
        readable, writeable, exceptional = select.select([self.client_socket], [], [], 1)
        if readable:
            response = self.client_socket.recv(4096).decode("utf-8")

            # If the server responds with "Welcome" then returns True, if not, then returns False
            if response == "Welcome":
                return True
            else:
                return False

    # Method that sends a user inputted text to the client socket
    def send(self, text):
        # Saves the text into a variable
        msg = text
        # Encodes it and sends it to the client socket
        self.client_socket.sendall(msg.encode("utf-8"))

    # Method that receives responses from the client socket from the server
    def receive(self):
        # Will loop as long as exit_receive event is not set
        while not self.exit_receive.is_set():
            # Uses select to check if there is a response from the server before calling recv()
            readable, writeable, exceptional = select.select([self.client_socket], [], [], 1)
            if readable:
                msg = self.client_socket.recv(4096).decode("utf-8")

                # If the message contains "server-shutdown", sets events and breaks out of the loop
                if msg == "server-shutdown":
                    self.exit_run.set()
                    self.exit_receive.set()
                    break
                # Prints out the message on the client terminal
                else:
                    print("\n" + msg)

    # Method that runs the client terminal
    def run(self):
        # Uses connect_server to check if the client is connected to the server
        connected = self.connect_server()

        # If it gets connected, then starts a thread to receive messages from server and other clients
        if connected:
            receiver = threading.Thread(target=self.receive)
            receiver.start()

            try:
                # Will loop as long as exit_run is not set
                while not self.exit_run.is_set():
                    # Asks the user for their chat message
                    user_msg = input("\nEnter a message (Type exit to quit): ")

                    # If the user decides to send "exit"
                    if user_msg.lower() == "exit":
                        # Sends the message to the server
                        msg = "exit"
                        self.client_socket.sendall(msg.encode("utf-8"))
                        # Sets the events and breaks the loop
                        self.exit_receive.set()
                        self.client_socket.close()
                        break

                    # If the message was not "exit", then only sends the message to the server to be displayed
                    self.client_socket.sendall(user_msg.encode("utf-8"))

            # Detects for a KeyboardInterrupt exception
            except KeyboardInterrupt:
                # Will send "exit" to the server and set the events
                msg = "exit"
                self.client_socket.sendall(msg.encode("utf-8"))
                self.exit_receive.set()
                self.client_socket.close()
                # Exits the thread
                receiver.join()


# UDP Server Class
class ServerUDP:
    # Constructor method
    def __init__(self, server_port):
        # Instance variables
        self.server_port = server_port
        self.local_addr = socket.gethostbyname(socket.gethostname())
        self.clients = {}
        self.messages = []

        # Setting up the UDP server
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        # Binding to local address and server port
        self.server_socket.bind((self.local_addr, self.server_port))

    # Method that helps the server accept a new client
    def accept_client(self, client_addr, message):
        try:
            # Obtains client name and saves it into a temp variable
            name = message

            # Cycles through the values in the client dictionary to see if the name entered is unique
            for i in self.clients.values():
                # If the name is a duplicate name of an already joined client
                if i == name:
                    # Sends "Name already taken" to the client and returns false
                    response = "Name already taken"
                    self.server_socket.sendto(response.encode(), client_addr)
                    return False

            # Adding user's unique name as value and client socket as the key into client dictionary
            self.clients[client_addr] = name
            # Adding client addr and join message as a tuple into the messages list
            new_conn = (client_addr, f"User {name} joined")
            self.messages.append(new_conn)
            # Sending "Welcome" to the client
            response = "Welcome"
            self.server_socket.sendto(response.encode(), client_addr)
            # Broadcasting a message to the server chat
            self.broadcast()
            # Returns True
            return True

        # Catches all exceptions and stops the server if an exception occurs
        except Exception as e:
            print(f"\nException: An exception ({e}) occurred while accepting the client.")
            self.shutdown()

    # Method that handles when a client leaves the chatroom
    def close_client(self, client_addr):
        try:
            # Grabbing user name
            name = self.clients[client_addr]
            # Removing the client socket from the dictionary using it as a key
            self.clients.pop(client_addr)
            # Appends client addr and leave message into messages list
            leave_msg = (client_addr, f"User {name} left")
            self.messages.append(leave_msg)
            # Calls on broadcast
            self.broadcast()
            # Returns True if client was successfully removed
            return True

        # Returns False if the key was not found
        except KeyError:
            return False

    # Method to broadcast a message to all connected clients
    def broadcast(self):
        # Extracting client address and message from the list
        temp_tuple = self.messages[-1]
        client_addr = temp_tuple[0]
        msg = temp_tuple[1]

        # Sending the message to all connected clients except for the one who sent it
        for i in self.clients:
            if i != client_addr:
                response = msg
                self.server_socket.sendto(response.encode(), i)

    # Method to shut down the server
    def shutdown(self):
        # Temp storage for all client sockets in the dictionary
        temp_client = []
        # Saves all connected clients into the list
        for i in self.clients:
            temp_client.append(i)

        # Loops through all connected clients in the list
        for j in temp_client:
            # Sends server-shutdown to all clients
            response = "server-shutdown"
            self.server_socket.sendto(response.encode(), j)
            # Terminates their connections
            self.close_client(j)

        # Closes server socket at the end
        self.server_socket.close()

    # Method that returns the number of connected clients to the chatroom
    def get_clients_number(self):
        # Getting the length of the dictionary
        client_no = len(self.clients)
        # Returning the length of the dictionary
        return client_no

    # Method that runs the UDP server
    def run(self):
        try:
            # Continually loops to keep server up and listen for client connections
            while True:
                # Receiving a message from the client
                msg, client_addr = self.server_socket.recvfrom(4096)
                client_msg = msg.decode()
                # Splitting client name and command
                temp = client_msg.split(":")
                name = temp[0]
                cmd = temp[1]

                # If the message is join
                if cmd.lower() == "join":
                    # Calls accept client to accept the incoming connection
                    self.accept_client(client_addr, name)
                # If the message is exit
                elif cmd.lower() == "exit":
                    # Closes the client
                    self.close_client(client_addr)
                # If the message is anything else
                else:
                    # Saves the message into the message list
                    temp_tuple = (client_addr, cmd)
                    self.messages.append(temp_tuple)
                    # Calls on broadcast to broadcast message to all clients
                    self.broadcast()

        # Detects for a KeyboardInterrupt error and shuts down the server if detected
        except KeyboardInterrupt:
            self.shutdown()

        # If any other Exception occurs, prints out the exception and shuts down the server
        except Exception as e:
            print(f"Exception {e} occurred while running the server.")
            self.shutdown()


# UDP Client Class
class ClientUDP:
    # Constructor method
    def __init__(self, client_name, server_port):
        # Setting up the server
        self.server_addr = socket.gethostbyname(socket.gethostname())
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

        # Instance variables
        self.server_port = server_port
        self.client_name = client_name

        # Setting up Threading Events
        self.exit_run = threading.Event()
        self.exit_receive = threading.Event()

    # Method that attempts a connection to the server
    def connect_server(self):
        # Calls on the send method with "join" as the message
        self.send("join")
        # Waits for a response from the server
        response, server_addr = self.client_socket.recvfrom(4096)
        server_resp = response.decode()

        # If the message received is Welcome, then connection is successful and returns True
        if server_resp == "Welcome":
            return True
        # If Welcome was not received, then connection is not successful and returns False
        else:
            return False

    # Method that sends a message to the server
    def send(self, text):
        # Sets up the message in a special format
        msg = f"{self.client_name}:{text}"
        # Sends the message to the server
        self.client_socket.sendto(msg.encode(), (self.server_addr, self.server_port))

    # Method that receives messages from the server
    def receive(self):
        # Will loop as long as exit_receive event is not set
        while not self.exit_receive.is_set():
            # Receives message from server and decodes it
            response, server_addr = self.client_socket.recvfrom(4096)
            msg = response.decode()

            # If the message contains "server-shutdown", sets events and breaks out of the loop
            if msg == "server-shutdown":
                self.exit_run.set()
                self.exit_receive.set()
                break
            # Prints out the message on the client terminal
            else:
                print("\n" + msg)

    # Method that runs the client
    def run(self):
        # Uses connect_server to check if the client is connected to the server
        connected = self.connect_server()

        # If it gets connected, then starts a thread to receive messages from server and other clients
        if connected:
            receiver = threading.Thread(target=self.receive)
            receiver.start()

            try:
                # Will loop as long as exit_run is not set
                while not self.exit_run.is_set():
                    # Asks the user for their chat message
                    user_msg = input("\nEnter a message (Type exit to quit): ")

                    # If the user decides to send "exit"
                    if user_msg.lower() == "exit":
                        # Sends the message to the server
                        msg = "exit"
                        self.client_socket.sendto(msg.encode(), (self.server_addr, self.server_port))
                        # Sets the events and breaks the loop
                        self.exit_receive.set()
                        self.client_socket.close()
                        break

                    # If the message was not "exit", then only sends the message to the server to be displayed
                    self.client_socket.sendto(user_msg.encode(), (self.server_addr, self.server_port))

            # Detects for a KeyboardInterrupt exception
            except KeyboardInterrupt:
                # Will send "exit" to the server and set the events
                msg = "exit"
                self.client_socket.sendto(msg.encode(), (self.server_addr, self.server_port))
                self.exit_receive.set()
                self.client_socket.close()
                # Exits the thread
                receiver.join()
