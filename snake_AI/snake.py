import pygame
import random
import numpy as np

# Initialize Pygame
pygame.init()

# Constants
WIDTH, HEIGHT = 400, 400
BLOCK_SIZE = 20
WHITE, GREEN, RED, BLACK = (255, 255, 255), (0, 255, 0), (255, 0, 0), (0, 0, 0)
MUTATION_RATE = 0.1  # Probability of modifying behavior
LEARNING_RATE = 0.05  # AI self-learning rate

# Set up display
screen = pygame.display.set_mode((WIDTH, HEIGHT))
clock = pygame.time.Clock()
font = pygame.font.Font(None, 24)

# Snake Class
class Snake:
    def __init__(self, brain=None):
        self.body = [(WIDTH // 2, HEIGHT // 2)]
        self.direction = (BLOCK_SIZE, 0)
        self.foods = [self.spawn_food(), self.spawn_food()]
        self.alive = True
        self.thought = ""
        self.steps = 0
        self.max_steps = 100  # Limit steps to prevent infinite loops
        
        # Neural weights: bias towards right, left, up, down (randomized)
        if brain is None:
            self.brain = np.random.rand(4)
        else:
            self.brain = self.adapt_logic(brain)
    
    def spawn_food(self):
        return (random.randint(0, (WIDTH // BLOCK_SIZE) - 1) * BLOCK_SIZE,
                random.randint(0, (HEIGHT // BLOCK_SIZE) - 1) * BLOCK_SIZE)
    
    def move(self):
        if not self.alive:
            return
        
        head_x, head_y = self.body[0]
        new_head = (head_x + self.direction[0], head_y + self.direction[1])
        
        # Check collisions
        if (new_head in self.body or new_head[0] < 0 or new_head[1] < 0 or
            new_head[0] >= WIDTH or new_head[1] >= HEIGHT or self.steps > self.max_steps):
            self.alive = False
            return
        
        self.body.insert(0, new_head)
        if new_head in self.foods:
            self.foods.remove(new_head)
            self.foods.append(self.spawn_food())
            self.steps = 0  # Reset step counter when eating
        else:
            self.body.pop()
        
        self.steps += 1
    
    def decide_move(self):
        head_x, head_y = self.body[0]
        
        # Find the closest food
        closest_food = min(self.foods, key=lambda f: abs(f[0] - head_x) + abs(f[1] - head_y))
        food_x, food_y = closest_food
        
        dist_x = food_x - head_x
        dist_y = food_y - head_y
        
        possible_moves = [
            ((BLOCK_SIZE, 0), "Right", self.brain[0]),
            ((-BLOCK_SIZE, 0), "Left", self.brain[1]),
            ((0, BLOCK_SIZE), "Down", self.brain[2]),
            ((0, -BLOCK_SIZE), "Up", self.brain[3])
        ]
        
        valid_moves = []
        for move, name, weight in possible_moves:
            new_x, new_y = head_x + move[0], head_y + move[1]
            if 0 <= new_x < WIDTH and 0 <= new_y < HEIGHT and (new_x, new_y) not in self.body:
                valid_moves.append((move, name, weight))
        
        if valid_moves:
            # Sort by neural preference and distance to food
            valid_moves.sort(key=lambda x: (abs((head_x + x[0][0]) - food_x) + abs((head_y + x[0][1]) - food_y), -x[2]))
            self.direction, self.thought = valid_moves[0][0], f"Moving {valid_moves[0][1]} (Neural choice)"
        else:
            self.alive = False  # No valid moves, AI dies
    
    def adapt_logic(self, parent_brain):
        new_brain = parent_brain.copy()
        if not self.alive:
            # If snake died by hitting a wall, reduce preference for that move
            if self.direction == (BLOCK_SIZE, 0):
                new_brain[0] -= LEARNING_RATE
            elif self.direction == (-BLOCK_SIZE, 0):
                new_brain[1] -= LEARNING_RATE
            elif self.direction == (0, BLOCK_SIZE):
                new_brain[2] -= LEARNING_RATE
            elif self.direction == (0, -BLOCK_SIZE):
                new_brain[3] -= LEARNING_RATE
            # Slightly increase preference for alternative moves
            for i in range(4):
                if new_brain[i] < 0:
                    new_brain[i] = 0  # Prevent negative weights
                else:
                    new_brain[i] += LEARNING_RATE * 0.5
        return new_brain

# Game Loop
best_snake = Snake()
running = True

def draw_snake(snake):
    for x, y in snake.body:
        pygame.draw.rect(screen, GREEN, (x, y, BLOCK_SIZE, BLOCK_SIZE))
    for food in snake.foods:
        pygame.draw.rect(screen, RED, (*food, BLOCK_SIZE, BLOCK_SIZE))
    
    # Display AI thoughts
    thought_text = font.render(f"AI: {snake.thought}", True, WHITE)
    step_text = font.render(f"Steps: {snake.steps}", True, WHITE)
    screen.blit(thought_text, (10, 10))
    screen.blit(step_text, (10, 30))

while running:
    screen.fill(BLACK)
    
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
    
    if best_snake.alive:
        best_snake.decide_move()
        best_snake.move()
        draw_snake(best_snake)
    else:
        # AI learns from its failures and adapts
        best_snake = Snake(best_snake.brain)
    
    pygame.display.flip()
    clock.tick(10)

pygame.quit()
