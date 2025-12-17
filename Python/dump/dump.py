import pygame
import sys

pygame.init()
screen = pygame.display.set_mode((600, 400))
clock = pygame.time.Clock()

x, y = 300, 200
speed = 5

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()

    keys = pygame.key.get_pressed()
    if keys[pygame.K_LEFT]: x -= speed
    if keys[pygame.K_RIGHT]: x += speed
    if keys[pygame.K_UP]: y -= speed
    if keys[pygame.K_DOWN]: y += speed

    screen.fill((30, 30, 30))
    pygame.draw.rect(screen, (0, 200, 200), (x, y, 50, 50))
    pygame.display.flip()
    clock.tick(60)
