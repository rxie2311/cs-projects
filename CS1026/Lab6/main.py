# Name: Raymond Xie
# Description: Lab 06
# Date: 2022/10/24

# Q1
f = open("text.txt", "r")
positive = []
negative = []
neutral = []

for line in f:
    entries = line.split(",")
    entries[1] = int(entries[1].rstrip("\n"))
    if entries[1] == 20:
        positive.append(entries[0])
    elif entries[1] == 0:
        neutral.append(entries[0])
    else:
        negative.append(entries[0])

tweet = "I really am very happy for you I love the weather I am also sad and have some regrets about being so tired"

tweetWords = tweet.split()
sentiment = 0
for word in tweetWords:
    if word in positive:
        sentiment += 20
    elif word in negative:
        sentiment -= 10

print("The positive keywords are {}".format(positive))
print("The neutral keywords are {}".format(neutral))
print("The negative keywords are {}".format(negative))
print("The sentiment of the tweet is {}".format(sentiment))

f.close()

# Q2
text = open("wordtext.txt","r")
# Error 1: Need to use "w" to overwrite items in the file
myfile = open("myfile.txt","w")

line = text.read()
words = line.split()

for word in words:
    # Error 2: Don't need the \n for print since it will auto print the words onto new lines
    print(word)
    # Error 3: myfile also needs \n for each word to be printed out on a separate line
    myfile.write(word + "\n")

# Close the files
text.close()
myfile.close()