<div class="container">
  <div class="main_block">
    <div class="header">
      <h1><?= $header ?></h1>
    </div>
    <form action=<?= $action ?> method="post" enctype="multipart/form-data">
  	  <input type="file" name="data_file" class="file" />
      <input type="submit" value="Send" class="button" />
    </form>
  </div>
</div>