# 9.2 Describe concepts associated with hashing

### Objectives

- [ ] Data distribution as it relates to hashing
- [ ] Hash function efficiency
- [ ] Hash collisions


### Answers

**Data distribution as it relates to hashing**
> Data distribution in reference to hashing is how uniformly the hash values are distributed across the hash space. Achieving even distribution is dependant on the hashing algorithm used. It should minimize collisions and be able to generate hashes evenly across the available hash range.

**Hash function efficiency**
> A hash function's efficiency is measured in how quickly/efficiently (required computational resources) it generates a hash value, how evenly it distributes its hash values across the hash space, and frequently collisions occur. 

**Hash collisions**
> A collision is when two different values generate the same hash. Collisions are inevitable but a good hashing function can reduce the likeliness of a collision.
