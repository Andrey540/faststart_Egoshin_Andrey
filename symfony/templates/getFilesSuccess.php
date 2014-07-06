<div class="container">
  <div class="main_block">
    <div class="header">
      <h1><?= $header ?></h1>
    </div>
      <ul>
        <?php foreach ($files as $file): ?>
          <li>
            <?php echo $file ?>
          </li>
        <?php endforeach ?>
      </ul>
  </div>
</div>